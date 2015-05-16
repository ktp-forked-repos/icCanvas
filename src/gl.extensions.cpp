#include <icCanvasManager.hpp>

icCanvasManager::GL::Extensions::Extensions() {};
icCanvasManager::GL::Extensions::~Extensions() {};

void icCanvasManager::GL::Extensions::collect_extensions(icCanvasManager::RefPtr<icCanvasManager::GL::ContextManager> m) {
    this->glCreateShader = (decltype(this->glCreateShader))m->get_proc_address("glCreateShader");
    this->glShaderSource = (decltype(this->glShaderSource))m->get_proc_address("glShaderSource");
    this->glCompileShader = (decltype(this->glCompileShader))m->get_proc_address("glCompileShader");
    this->glGetShaderiv = (decltype(this->glGetShaderiv))m->get_proc_address("glGetShaderiv");
    this->glGetShaderInfoLog = (decltype(this->glGetShaderInfoLog))m->get_proc_address("glGetShaderInfoLog");
    this->glDeleteShader = (decltype(this->glDeleteShader))m->get_proc_address("glDeleteShader");
    this->glCreateProgram = (decltype(this->glCreateProgram))m->get_proc_address("glCreateProgram");
    this->glAttachShader = (decltype(this->glAttachShader))m->get_proc_address("glAttachShader");
    this->glLinkProgram = (decltype(this->glLinkProgram))m->get_proc_address("glLinkProgram");
    this->glGetProgramiv = (decltype(this->glGetProgramiv))m->get_proc_address("glGetProgramiv");
    this->glGetProgramInfoLog = (decltype(this->glGetProgramInfoLog))m->get_proc_address("glGetProgramInfoLog");
    this->glDeleteProgram = (decltype(this->glDeleteProgram))m->get_proc_address("glDeleteProgram");
    this->glDetachShader = (decltype(this->glDetachShader))m->get_proc_address("glDetachShader");
    this->glGenFramebuffers = (decltype(this->glGenFramebuffers))m->get_proc_address("glGenFramebuffers");
    this->glDeleteFramebuffers = (decltype(this->glDeleteFramebuffers))m->get_proc_address("glDeleteFramebuffers");
    this->glBindFramebuffer = (decltype(this->glBindFramebuffer))m->get_proc_address("glBindFramebuffer");
    this->glFramebufferTexture = (decltype(this->glFramebufferTexture))m->get_proc_address("glFramebufferTexture");
    this->glFramebufferTexture1D = (decltype(this->glFramebufferTexture1D))m->get_proc_address("glFramebufferTexture1D");
    this->glFramebufferTexture2D = (decltype(this->glFramebufferTexture2D))m->get_proc_address("glFramebufferTexture2D");
    this->glFramebufferTexture3D = (decltype(this->glFramebufferTexture3D))m->get_proc_address("glFramebufferTexture3D");
    this->glCheckFramebufferStatus = (decltype(this->glCheckFramebufferStatus))m->get_proc_address("glCheckFramebufferStatus");
    this->glDrawBuffer = (decltype(this->glDrawBuffer))m->get_proc_address("glDrawBuffer");
    this->glGenTextures = (decltype(this->glGenTextures))m->get_proc_address("glGenTextures");
    this->glBindTexture = (decltype(this->glBindTexture))m->get_proc_address("glBindTexture");
    this->glDeleteTextures = (decltype(this->glDeleteTextures))m->get_proc_address("glDeleteTextures");
    this->glTexImage1D = (decltype(this->glTexImage1D))m->get_proc_address("glTexImage1D");
    this->glTexImage2D = (decltype(this->glTexImage2D))m->get_proc_address("glTexImage2D");
    this->glGenBuffers = (decltype(this->glGenBuffers))m->get_proc_address("glGenBuffers");
    this->glDeleteBuffers = (decltype(this->glDeleteBuffers))m->get_proc_address("glDeleteBuffers");
    this->glBindBuffer = (decltype(this->glBindBuffer))m->get_proc_address("glBindBuffer");
    this->glBufferData = (decltype(this->glBufferData))m->get_proc_address("glBufferData");
    this->glVertexAttribPointer = (decltype(this->glVertexAttribPointer))m->get_proc_address("glVertexAttribPointer");
    this->glVertexAttribIPointer = (decltype(this->glVertexAttribIPointer))m->get_proc_address("glVertexAttribIPointer");
    this->glVertexAttribLPointer = (decltype(this->glVertexAttribLPointer))m->get_proc_address("glVertexAttribLPointer");
    this->glGenVertexArrays = (decltype(this->glGenVertexArrays))m->get_proc_address("glGenVertexArrays");
    this->glDeleteVertexArrays = (decltype(this->glDeleteVertexArrays))m->get_proc_address("glDeleteVertexArrays");
    this->glBindVertexArray = (decltype(this->glBindVertexArray))m->get_proc_address("glBindVertexArray");
    this->glEnableVertexAttribArray = (decltype(this->glEnableVertexAttribArray))m->get_proc_address("glEnableVertexAttribArray");
    this->glDisableVertexAttribArray = (decltype(this->glDisableVertexAttribArray))m->get_proc_address("glDisableVertexAttribArray");
    this->glGetActiveAttrib = (decltype(this->glGetActiveAttrib))m->get_proc_address("glGetActiveAttrib");
    this->glGetAttribLocation = (decltype(this->glGetAttribLocation))m->get_proc_address("glGetAttribLocation");
    this->glGetFragDataLocation = (decltype(this->glGetFragDataLocation))m->get_proc_address("glGetFragDataLocation");
    this->glGetFragDataIndex = (decltype(this->glGetFragDataIndex))m->get_proc_address("glGetFragDataIndex");
    this->glGetUniformIndices = (decltype(this->glGetUniformIndices))m->get_proc_address("glGetUniformIndices");
    this->glGetActiveUniformName = (decltype(this->glGetActiveUniformName))m->get_proc_address("glGetActiveUniformName");
    this->glGetActiveUniformsiv = (decltype(this->glGetActiveUniformsiv))m->get_proc_address("glGetActiveUniformsiv");
    this->glGetUniformLocation = (decltype(this->glGetUniformLocation))m->get_proc_address("glGetUniformLocation");
    this->glUniform1f = (decltype(this->glUniform1f))m->get_proc_address("glUniform1f");
    this->glUniform2f = (decltype(this->glUniform2f))m->get_proc_address("glUniform2f");
    this->glUniform3f = (decltype(this->glUniform3f))m->get_proc_address("glUniform3f");
    this->glUniform4f = (decltype(this->glUniform4f))m->get_proc_address("glUniform4f");
    this->glUniform1i = (decltype(this->glUniform1i))m->get_proc_address("glUniform1i");
    this->glUniform2i = (decltype(this->glUniform2i))m->get_proc_address("glUniform2i");
    this->glUniform3i = (decltype(this->glUniform3i))m->get_proc_address("glUniform3i");
    this->glUniform4i = (decltype(this->glUniform4i))m->get_proc_address("glUniform4i");
    this->glUniform1ui = (decltype(this->glUniform1ui))m->get_proc_address("glUniform1ui");
    this->glUniform2ui = (decltype(this->glUniform2ui))m->get_proc_address("glUniform2ui");
    this->glUniform3ui = (decltype(this->glUniform3ui))m->get_proc_address("glUniform3ui");
    this->glUniform4ui = (decltype(this->glUniform4ui))m->get_proc_address("glUniform4ui");
    this->glUniform1fv = (decltype(this->glUniform1fv))m->get_proc_address("glUniform1fv");
    this->glUniform2fv = (decltype(this->glUniform2fv))m->get_proc_address("glUniform2fv");
    this->glUniform3fv = (decltype(this->glUniform3fv))m->get_proc_address("glUniform3fv");
    this->glUniform4fv = (decltype(this->glUniform4fv))m->get_proc_address("glUniform4fv");
    this->glUniform1iv = (decltype(this->glUniform1iv))m->get_proc_address("glUniform1iv");
    this->glUniform2iv = (decltype(this->glUniform2iv))m->get_proc_address("glUniform2iv");
    this->glUniform3iv = (decltype(this->glUniform3iv))m->get_proc_address("glUniform3iv");
    this->glUniform4iv = (decltype(this->glUniform4iv))m->get_proc_address("glUniform4iv");
    this->glUniform1uiv = (decltype(this->glUniform1uiv))m->get_proc_address("glUniform1uiv");
    this->glUniform2uiv = (decltype(this->glUniform2uiv))m->get_proc_address("glUniform2uiv");
    this->glUniform3uiv = (decltype(this->glUniform3uiv))m->get_proc_address("glUniform3uiv");
    this->glUniform4uiv = (decltype(this->glUniform4uiv))m->get_proc_address("glUniform4uiv");
    this->glUniformMatrix2fv = (decltype(this->glUniformMatrix2fv))m->get_proc_address("glUniformMatrix2fv");
    this->glUniformMatrix3fv = (decltype(this->glUniformMatrix3fv))m->get_proc_address("glUniformMatrix3fv");
    this->glUniformMatrix4fv = (decltype(this->glUniformMatrix4fv))m->get_proc_address("glUniformMatrix4fv");
    this->glUniformMatrix2x3fv = (decltype(this->glUniformMatrix2x3fv))m->get_proc_address("glUniformMatrix2x3fv");
    this->glUniformMatrix3x2fv = (decltype(this->glUniformMatrix3x2fv))m->get_proc_address("glUniformMatrix3x2fv");
    this->glUniformMatrix2x4fv = (decltype(this->glUniformMatrix2x4fv))m->get_proc_address("glUniformMatrix2x4fv");
    this->glUniformMatrix4x2fv = (decltype(this->glUniformMatrix4x2fv))m->get_proc_address("glUniformMatrix4x2fv");
    this->glUniformMatrix3x4fv = (decltype(this->glUniformMatrix3x4fv))m->get_proc_address("glUniformMatrix3x4fv");
    this->glUniformMatrix4x3fv = (decltype(this->glUniformMatrix4x3fv))m->get_proc_address("glUniformMatrix4x3fv");
    this->glUseProgram = (decltype(this->glUseProgram))m->get_proc_address("glUseProgram");
    this->glClearBufferiv = (decltype(this->glClearBufferiv))m->get_proc_address("glClearBufferiv");
    this->glClearBufferuiv = (decltype(this->glClearBufferuiv))m->get_proc_address("glClearBufferuiv");
    this->glClearBufferfv = (decltype(this->glClearBufferfv))m->get_proc_address("glClearBufferfv");
    this->glClearBufferfi = (decltype(this->glClearBufferfi))m->get_proc_address("glClearBufferfi");
    this->glActiveTexture = (decltype(this->glActiveTexture))m->get_proc_address("glActiveTexture");
    this->glDrawArrays = (decltype(this->glDrawArrays))m->get_proc_address("glDrawArrays");
    this->glCopyTexImage2D = (decltype(this->glCopyTexImage2D))m->get_proc_address("glCopyTexImage2D");
    this->glCopyTexImage1D = (decltype(this->glCopyTexImage1D))m->get_proc_address("glCopyTexImage1D");
    //this-> = (decltype(this->))m->get_proc_address("");
}
