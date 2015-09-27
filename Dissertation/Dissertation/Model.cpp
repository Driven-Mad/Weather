#include "Model.h"


Model::Model(char *objectFP, char *fragShaderFP, char *vertShaderFP){
	// Initialise variables
	VAO = 0;
	program = 0;
	shaderModelMatLocation = shaderViewMatLocation = shaderProjMatLocation = 0;
	position = glm::vec3(0.0f,0.0f,0.0f);
	numVerts = 0;
	objFP = objectFP;
	fragFP = fragShaderFP;
	vertFP = vertShaderFP;
	// Create the model
	initaliseVAO();
	// Create the shaders
	initaliseShaders();
	modelMatrix = glm::translate(glm::mat4(1.0f), position );
}


Model::~Model(void){
}

void Model::initaliseVAO(){
	// Creates one VAO
	glGenVertexArrays( 1, &VAO );
	glBindVertexArray(VAO );
	// 'Binding' something makes it the current one we are using
	// This is like activating it, so that subsequent function calls will work on this item
	
	//containers for the different attributes of the model

	//make an object loader
	ObjectLoader* OBJ = new ObjectLoader();
	//load in an object
	OBJ->loadOBJ(objFP, out_Verts, out_UVs, out_Normals, out_Tangents, out_BiTangents);
	//make a texture loader.
	
	
	// Number of vertices in above data
	numVerts = out_Verts.size();

	//Same for all buffers 0-4
	//Variable for storing a VBO, generate a buffer, 
	//then "bind"/actiate it to the VBO, apply the data, 
	//then link to the shader via pointer & enable the array.
	//0
	GLuint positionBuffer = 0;
	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, out_Verts.size() * sizeof(glm::vec3), &out_Verts[0] ,GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0 );
	glEnableVertexAttribArray(0);
	//1
	GLuint normalBuffer = 0;
	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, out_Normals.size() * sizeof(glm::vec3), &out_Normals[0],GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof(glm::vec3), 0 );
	glEnableVertexAttribArray(1);
	//2
	GLuint UVBuffer = 0;
	glGenBuffers(1, &UVBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, UVBuffer);
	glBufferData(GL_ARRAY_BUFFER, out_UVs.size() * sizeof(glm::vec2), &out_UVs[0],GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,  sizeof(glm::vec2), 0 );
	glEnableVertexAttribArray(2);
	//3
	GLuint TanBuffer = 0;
	glGenBuffers(1, &TanBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, TanBuffer);
	glBufferData(GL_ARRAY_BUFFER, out_Tangents.size() * sizeof(glm::vec3), &out_Tangents[0], GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(3);
	//4
	GLuint BiTanBuffer = 0;
	glGenBuffers(1, &BiTanBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, BiTanBuffer);
	glBufferData(GL_ARRAY_BUFFER, out_BiTangents.size() * sizeof(glm::vec3), &out_BiTangents[0], GL_STATIC_DRAW);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(4);

	//unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray( 0 );
}

void Model::initaliseShaders(){
	ProgramLoader *pgLoad = new ProgramLoader();
	//make a program for the specified frag and vertex shaders
	pgLoad->loadProgram(vertFP, fragFP);
	program = pgLoad->getProgram(); 
	//get all the locations in the program to link the application to the shaders.
	shaderModelMatLocation = glGetUniformLocation( program, "modelMat" );
	shaderViewMatLocation = glGetUniformLocation( program, "viewMat" );
	shaderProjMatLocation = glGetUniformLocation( program, "projMat" );
	shader3X3Location = glGetUniformLocation(program, "MV3x3");
}

void Model::update(float DT){
	modelMatrix = glm::translate(glm::mat4(1.0f), position );
}

void Model::draw(glm::mat4 viewMatrix, glm::mat4 projMatrix){
	// Activate the shader program
	glUseProgram( program );

		// Activate the VAO
		glBindVertexArray( VAO );
			//create a model matrix 3x3 for my normals.
			modelViewMatrix3x3 = glm::mat3(viewMatrix * modelMatrix);
			glEnable(GL_CULL_FACE);
			glFrontFace(GL_CCW);
			// Send matrices to the shader as uniforms like this:
			glUniformMatrix4fv(shaderModelMatLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix) );
			glUniformMatrix4fv(shaderViewMatLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix) );
			glUniformMatrix4fv(shaderProjMatLocation, 1, GL_FALSE, glm::value_ptr(projMatrix) );
			glUniformMatrix3fv(shader3X3Location, 1, GL_FALSE, glm::value_ptr(modelViewMatrix3x3));

			// Tell OpenGL to draw it
			// Must specify the type of geometry to draw and the number of vertices
			glDrawArrays(GL_TRIANGLES, 0,numVerts);
		// Unbind VAO
		glBindVertexArray( 0 );
	// Technically we can do this, but it makes no real sense because we must always have a valid shader program to draw geometry
	glUseProgram( 0 );
}

void Model::setPosition(glm::vec3 a){
	position = a;
}

void Model::setRotation(glm::vec3 a){
	rotation = a;
}

glm::vec3 Model::getPosition(){
	return position;
}

glm::vec3 Model::getRotation(){
	return rotation;
}

GLint Model::getProgram(){
		return program;
}

glm::mat4 Model::getModelMatrix(){
	return modelMatrix;
}
void Model::setModelMatrix(glm::mat4 a){
	modelMatrix = a;
}