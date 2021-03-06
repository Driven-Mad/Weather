#include "ProgramLoader.h"

ProgramLoader::ProgramLoader(void){
	// The 'program' stores the shaders
	program = glCreateProgram();
}


ProgramLoader::~ProgramLoader(void){
}
void ProgramLoader::loadVShader(char *filepath){
	//reads in the file into a buffer
	std::ifstream t(filepath);
	std::stringstream buffer;
	buffer << t.rdbuf();
	Vdata = buffer.str();
	if(Vdata.size() == NULL){
		std::ofstream newFile;
		newFile.open(filepath);
		newFile <<"#version 330\n }";
		newFile.close();
		printf("\n NEW FILE WAS CREATED: %s", filepath);
	}
	// Create the vertex shader
	vShader = glCreateShader( GL_VERTEX_SHADER );
	//find the size of the Vdata
	int length = Vdata.length();
	//get our shader
	const GLchar* vStr = Vdata.c_str();
	// Give GL the source for it
	glShaderSource( vShader, 1, &vStr, NULL );
	// Compile the shader
	glCompileShader( vShader );
	// Check it compiled and give useful output if it didn't work!
	if( CheckShaderCompiled( vShader ) ){
		printf("\n %s successfully compiled", filepath);
	}
	else{
		printf("\n %s failed to compiled", filepath);
		return;
	}
	// This links the shader to the program
	glAttachShader( program, vShader );
	// This makes sure the vertex and fragment shaders connect together
	glLinkProgram( program );
}

void ProgramLoader::loadGShader(char *filepath){
	//reads in the file into a buffer
	std::ifstream t(filepath);
	std::stringstream buffer;
	buffer << t.rdbuf();
	Gdata = buffer.str();
	if(Gdata.size() == NULL){
		std::ofstream newFile;
		newFile.open(filepath);
		newFile <<"#version 330\n }";
		newFile.close();
		printf("\n NEW FILE WAS CREATED: %s", filepath);
	}
	// Create the vertex shader
	gShader = glCreateShader( GL_GEOMETRY_SHADER );
	//find the size of the Vdata
	int length = Gdata.length();
	//get our shader
	const GLchar* gStr = Gdata.c_str();
	// Give GL the source for it
	glShaderSource( gShader, 1, &gStr, NULL );
	// Compile the shader
	glCompileShader( gShader );
	// Check it compiled and give useful output if it didn't work!
	if( CheckShaderCompiled( gShader ) ){
		printf("\n %s successfully compiled", filepath);
	}
	else{
		printf("\n %s failed to compiled", filepath);
		return;
	}
	// This links the shader to the program
	glAttachShader( program, gShader );
	// This makes sure the vertex and fragment shaders connect together
	glLinkProgram( program );
}

void ProgramLoader::loadFShader(char *filepath){
	//reads in the file into a buffer
	std::ifstream t(filepath);
	std::stringstream buffer;
	buffer << t.rdbuf();
	Fdata = buffer.str();
	if(Fdata.size() == NULL){
		std::ofstream newFile;
		newFile.open(filepath);
		newFile <<"#version 330\n }";
		newFile.close();
		printf("\n NEW FILE WAS CREATED: %s", filepath);
	}
	// Create the fragment shader
	fShader = glCreateShader( GL_FRAGMENT_SHADER );
	//find the size of the fdata
	int length = Fdata.length();
	//get our shader
	const GLchar* fStr = Fdata.c_str();
	// Give GL the source for it
	glShaderSource( fShader, 1, &fStr, NULL );
	//compile the shader
	glCompileShader( fShader );
	// Check it compiled and give useful output if it didn't work!
	if( CheckShaderCompiled( fShader ) )
	{
		printf("\n %s successfully compiled", filepath);
	}else{
		printf("\n %s failed to compiled", filepath);
		return;
	}
	glAttachShader( program, fShader );
	// This makes sure the vertex and fragment shaders connect together
	glLinkProgram( program );
}

bool ProgramLoader::CheckShaderCompiled( GLint shader ){
	GLint compiled;
	glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
	if ( !compiled ){
		GLsizei len;
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &len );
		// OpenGL will store an error message as a string that we can retrieve and print
		GLchar* log = new GLchar[len+1];
		glGetShaderInfoLog( shader, len, &len, log );
		std::cerr << "ERROR: Shader compilation failed: " << log << std::endl;
		delete [] log;
		return false;
	}
	return true;
}

void ProgramLoader::loadProgram(char *vShaderFP, char *fShaderFP){
	//loads the vertex shader
	loadVShader(vShaderFP);
	//loads the fragent shader
	loadFShader(fShaderFP);
	// Check this worked
	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked );
	if ( linked ){
		printf("\n Program successfully linked");		
	}
	else{
		GLsizei len;
		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &len );
		GLchar* log = new GLchar[len+1];
		glGetProgramInfoLog( program, len, &len, log );
		std::cerr << "ERROR: Shader linking failed: " << log << std::endl;
		delete [] log;
		return;
	}
}

void ProgramLoader::loadProgram(char *vShaderFP, char *fShaderFP, char *gShaderFP){
	//loads the vertex shader
	loadVShader(vShaderFP);
	//loads the fragent shader
	loadFShader(fShaderFP);
	//loads the fragent shader
	loadGShader(gShaderFP);
	// Check this worked
	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked );
	if ( linked ){
		printf("\n Program successfully linked");		
	}
	else{
		GLsizei len;
		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &len );
		GLchar* log = new GLchar[len+1];
		glGetProgramInfoLog( program, len, &len, log );
		std::cerr << "ERROR: Shader linking failed: " << log << std::endl;
		delete [] log;
		return;
	}
}

GLint ProgramLoader::getProgram(){
	//returns the program from storage
	return program;
}




