package com.example.gl2java;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.opengl.GLES20;

public class GL2JavaView extends GLSurfaceView{

	private static String TAG = "GL2JavaView";
	
    public GL2JavaView(Context context) {
		super(context);
	    init();	
	}
	
    public GL2JavaView(Context context, AttributeSet attrs) {
		super(context, attrs);
		init();
	}
    
    private void init() {
    	setEGLContextClientVersion(2);
    	setRenderer(new Renderer());
    }

	private static class Renderer implements GLSurfaceView.Renderer {
		
		public Renderer() {
			mTriangleVertices = ByteBuffer.allocateDirect(mTriangleVerticesData.length * 4)
					.order(ByteOrder.nativeOrder()).asFloatBuffer();
			mTriangleVertices.put(mTriangleVerticesData).position(0);
		}

		@Override
		public void onSurfaceCreated(GL10 gl, EGLConfig config) {
			// TODO Auto-generated method stub
			mProgram = createProgram(mVertexShader, mFragmentShader);
			if (0 == mProgram) {
				Log.e(TAG, "create opengles program fails");
				return;
			}
			
			mvPositionHandle = GLES20.glGetAttribLocation(mProgram, "vPosition");
			checkGlError("glGetAttribLocation");
			if (-1 == mvPositionHandle) {
				throw new RuntimeException("Could not get attrib location for vPosition");
			}
		}

		@Override
		public void onSurfaceChanged(GL10 gl, int width, int height) {
			GLES20.glViewport(0,  0,  width, height);
		}

		@Override
		public void onDrawFrame(GL10 gl) {
			GLES20.glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
			GLES20.glClear(GLES20.GL_DEPTH_BUFFER_BIT | GLES20.GL_COLOR_BUFFER_BIT);
		    GLES20.glUseProgram(mProgram);
		    checkGlError("glUseProgram");

		    GLES20.glVertexAttribPointer(mvPositionHandle, 2, GLES20.GL_FLOAT, false, 0, mTriangleVertices);
		    checkGlError("glVertexAttribPointer");
		    GLES20.glEnableVertexAttribArray(mvPositionHandle);
		    checkGlError("glEnableVertexAttribArray");
		    GLES20.glDrawArrays(GLES20.GL_TRIANGLES, 0, 3);
		    checkGlError("glDrawArrays");
		}
		
		private int loadShader(int shaderType, String source) {
			int shader = GLES20.glCreateShader(shaderType);
			if (0 != shader) {
				GLES20.glShaderSource(shader, source);
				GLES20.glCompileShader(shader);
				int[] compiledStatus = new int[1];
				GLES20.glGetShaderiv(shader, GLES20.GL_COMPILE_STATUS, compiledStatus, 0);
				if (0 == compiledStatus[0]) {
					Log.e(TAG, "Could not compile shader " + shaderType + " : ");
					Log.e(TAG, GLES20.glGetShaderInfoLog(shader));
					GLES20.glDeleteShader(shader);
					shader = 0;
				}
			}
			
			return shader;
		}
		
		private int createProgram(String vertexSource, String fragmentSource) {
			int vertexShader = loadShader(GLES20.GL_VERTEX_SHADER, vertexSource);
			if (0 == vertexShader) {
				Log.e(TAG, "load vertexShader fails");
				return 0;
			}
			
			int fragmentShader = loadShader(GLES20.GL_FRAGMENT_SHADER, fragmentSource);
			if (0 == fragmentShader) {
				Log.e(TAG, "load fragmentShader fails");
				return 0;
			}
			
			int program = GLES20.glCreateProgram();
			if (0 != program) {
				GLES20.glAttachShader(program, vertexShader);
				checkGlError("glDetachShader vertexShader");
				GLES20.glAttachShader(program, fragmentShader);
				checkGlError("glDetechShader fragmentShader");
				GLES20.glLinkProgram(program);
				int[] linkedStatus = new int[1];
				GLES20.glGetProgramiv(program, GLES20.GL_LINK_STATUS, linkedStatus, 0);
				if (0 == linkedStatus[0]) {
					Log.e(TAG, "Could not link program : ");
					Log.e(TAG, GLES20.glGetProgramInfoLog(program));
					GLES20.glDeleteProgram(program);
					program = 0;
				}
			}
			
			return program;
		}
		
		private void checkGlError(String op) {
			int error;
			while ((error = GLES20.glGetError()) != GLES20.GL_NO_ERROR) {
				Log.e(TAG, op + " : glError " + error);
				throw new RuntimeException(op + " : glError " + error);
			}
		}
		
		private final float[] mTriangleVerticesData = { 0.0f, 0.5f, -0.5f, -0.5f,
				0.5f, -0.5f };
		
		private FloatBuffer mTriangleVertices;
		
		private final String mVertexShader = "attribute vec4 vPosition;\n"
		    + "void main() {\n"
		    + "  gl_Position = vPosition;\n"
		    + "}\n";
		
		private final String mFragmentShader = "precision mediump float;\n"
		    + "void main() {\n"
		    + "  gl_FragColor = vec4(0.0, 1.0, 1.0, 1.0);\n"
		    + "}\n";
				
		
		private int mProgram;
		private int mvPositionHandle;
	}
}
