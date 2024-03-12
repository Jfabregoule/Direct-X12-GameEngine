#pragma once
#include "Engine.h"
#include "DirectX12/Vertex.h"
#include <DirectXColors.h>
#include <vector>

using namespace DirectX;

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									 CubeMesh Struct 									|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region SkyBox Struct

struct ENGINE_API SkyBox {

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |									    Attributes 									    |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Attributes

	Vertex skybox[24];
	UINT skyboxVerticesCount = 24; // Taille du tableau cube

	UINT skyboxIndices[36] =
	{
		 0, 2, 1,
		 2, 0, 3,

		 //// left face
		 6, 4, 5,
		 4, 6, 7,

		 //// back face
		 9, 11, 10,
		 11, 9, 8,

		 //////// right face
		 14, 12, 13,
		 12, 14, 15,

		 //////// top face
		 18, 16, 17,
		 16, 18, 19,

		 //////// bottom face
		 20, 22, 21,
		 22, 20, 23,
	};
	UINT skyboxIndicesCount = sizeof(skyboxIndices) / sizeof(UINT);

#pragma endregion

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |									    Methods 									    |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region Methods

	void GenerateSkybox() 
	{
		skybox[0] = Vertex({ XMFLOAT3(-100.0f, 100.0f, -100.0f), XMFLOAT4(Colors::White),XMFLOAT2(0,0) });//0
		skybox[1] = Vertex({ XMFLOAT3(100.0f, 100.0f, -100.0f), XMFLOAT4(Colors::White),XMFLOAT2(0,1) });//1
		skybox[2] = Vertex({ XMFLOAT3(100.0f, -100.0f, -100.0f), XMFLOAT4(Colors::Black),XMFLOAT2(1,1) });//2
		skybox[3] = Vertex({ XMFLOAT3(-100.0f, -100.0f, -100.0f), XMFLOAT4(Colors::Black),XMFLOAT2(1,0) });//3

		skybox[4] = Vertex({ XMFLOAT3(-100.0f, 100.0f, -100.0f), XMFLOAT4(Colors::White),XMFLOAT2(0,0) });//4
		skybox[5] = Vertex({ XMFLOAT3(-100.0f, 100.0f, 100.0f), XMFLOAT4(Colors::White),XMFLOAT2(0,1) });//5
		skybox[6] = Vertex({ XMFLOAT3(-100.0f, -100.0f, 100.0f), XMFLOAT4(Colors::Black) ,XMFLOAT2(1,1) });//6
		skybox[7] = Vertex({ XMFLOAT3(-100.0f, -100.0f, -100.0f), XMFLOAT4(Colors::Black),XMFLOAT2(1,0) });//7

		skybox[8] = Vertex({ XMFLOAT3(-100.0f, -100.0f, 100.0f), XMFLOAT4(Colors::White), XMFLOAT2(0,0) });//8
		skybox[9] = Vertex({ XMFLOAT3(100.0f, -100.0f, 100.0f), XMFLOAT4(Colors::White), XMFLOAT2(0,1) });//9
		skybox[10] = Vertex({ XMFLOAT3(100.0f, 100.0f, 100.0f), XMFLOAT4(Colors::Black), XMFLOAT2(1,1) });//10
		skybox[11] = Vertex({ XMFLOAT3(-100.0f, 100.0f, 100.0f), XMFLOAT4(Colors::Black), XMFLOAT2(1,0) });//11

		skybox[12] = Vertex({ XMFLOAT3(100.0f, 100.0f, 100.0f), XMFLOAT4(Colors::White),XMFLOAT2(0,0) });//12
		skybox[13] = Vertex({ XMFLOAT3(100.0f, 100.0f, -100.0f), XMFLOAT4(Colors::White),XMFLOAT2(0,1) });//13
		skybox[14] = Vertex({ XMFLOAT3(100.0f, -100.0f, -100.0f), XMFLOAT4(Colors::Black),XMFLOAT2(1,1) });//14
		skybox[15] = Vertex({ XMFLOAT3(100.0f, -100.0f, 100.0f), XMFLOAT4(Colors::Black) ,XMFLOAT2(1,0) });//15

		skybox[16] = Vertex({ XMFLOAT3(-100.0f, 100.0f, 100.0f), XMFLOAT4(Colors::White),XMFLOAT2(0,0) });//16
		skybox[17] = Vertex({ XMFLOAT3(-100.0f, 100.0f, -100.0f), XMFLOAT4(Colors::White),XMFLOAT2(0,1) });//17
		skybox[18] = Vertex({ XMFLOAT3(100.0f, 100.0f, -100.0f), XMFLOAT4(Colors::Black) ,XMFLOAT2(1,1) }); // 18
		skybox[19] = Vertex({ XMFLOAT3(100.0f, 100.0f, 100.0f), XMFLOAT4(Colors::Black),XMFLOAT2(1,0) });//19

		skybox[20] = Vertex({ XMFLOAT3(-100.0f, -100.0f, 100.0f), XMFLOAT4(Colors::White),XMFLOAT2(0,0) });//20
		skybox[21] = Vertex({ XMFLOAT3(-100.0f, -100.0f, -100.0f), XMFLOAT4(Colors::White),XMFLOAT2(0,1) });//21
		skybox[22] = Vertex({ XMFLOAT3(100.0f, -100.0f, -100.0f), XMFLOAT4(Colors::Black) ,XMFLOAT2(1,1) });//22
		skybox[23] = Vertex({ XMFLOAT3(100.0f, -100.0f, 100.0f), XMFLOAT4(Colors::Black),XMFLOAT2(1,0) });//23
	};

#pragma endregion

};

#pragma endregion