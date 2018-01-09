#pragma once

#include <GL/glew.h>

class DepthBuffer {
	public:
		DepthBuffer();
		~DepthBuffer();

		void Create(int resolution);
	
		void bind();
		void unbind();
		void bindDepthMap();
		void unbindDepthMap();

	private:
		GLuint _framebuffer;
		GLuint _depthmap;
		GLsizei _resolution;

};