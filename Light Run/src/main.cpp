//MARMALADE SPECIFIC
//#include "s3e.h"

#include "AppDelegate.h"

int main()
{
	//MARMALADE SPECIFIC
	// to exit correctly, applications should poll for quit requests
	//while(!s3eDeviceCheckQuitRequest())
	//{
	AppDelegate* app;
	int nRet = 0;
	
	app = new AppDelegate;
	nRet = cocos2d::CCApplication::sharedApplication().Run();;
	delete app;
	return nRet;
	
		//MARMALADE SPECIFIC
		// S3E applications should yield frequently
	//	s3eDeviceYield();
	//}


	//return 0;
}
