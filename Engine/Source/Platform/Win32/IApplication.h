#pragma once

#define ENTRYAPP(x) Win32::IApplication* EntryApplication() { return new x; }

/*
*  -------------------------------------------------------------------------------------
* |                                                                                     |
* |									 Win32 Namespace 									|
* |                                                                                     |
*  -------------------------------------------------------------------------------------
*/

#pragma region Win32 Namespace

namespace Win32 {

	/*
	*  -------------------------------------------------------------------------------------
	* |                                                                                     |
	* |								IApplication Class 									    |
	* |                                                                                     |
	*  -------------------------------------------------------------------------------------
	*/

#pragma region IApplication Class

	class ENGINE_API IApplication {

		// Application

	public:

		/*
		*  -------------------------------------------------------------------------------------
		* |                                                                                     |
		* |								Constructor/Destructor 									|
		* |                                                                                     |
		*  -------------------------------------------------------------------------------------
		*/

#pragma region Constructor And Destructor

		/* Application Constuctor */
		IApplication();

		/* Application Deconstructor */
		virtual ~IApplication() {};

#pragma endregion


	public:

		/*
		*  -------------------------------------------------------------------------------------
		* |                                                                                     |
		* |									    Methods 									    |
		* |                                                                                     |
		*  -------------------------------------------------------------------------------------
		*/

#pragma region Methods

		/* Called to setup our pergame settings  */
		virtual VOID SetupPerGameSettings() = 0;

		/* Called to Initialize the Application  */
		virtual VOID PreInitialize() = 0;

		/* Called to Initialize the Application  */
		virtual VOID Initialize() = 0;

		/* Game Loop - Called on a loop while the Application is running */
		virtual VOID Update() = 0;
	};

#pragma endregion

	IApplication* EntryApplication();

#pragma endregion

}

#pragma endregion