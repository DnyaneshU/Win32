#include<Windows.h>

//Global Callback Declaration 
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);//this is declator:(HWND, UINT, WPARAM, LPARAM).
//Entry-point Function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)//WINAPI is calling  convention. This is declarator: (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[]=TEXT("DMU_WINDOW");//TCHAR CAN BE char or wchar

	//code
	ZeroMemory((void*)&wndclass, sizeof(WNDCLASSEX));//this part: ZeroMemory((void*) is telling to free up our memory in the ram by giving it the address. This is our macro function.Kadhi pan struct bhartana asa compulsary nahi ki tumhi akha struct bhara. Mhanunach tumhala jevdhe havet te liha and baaki sagle 0 kara.

	//Initialising Window Class
	// all these are members of wndclass. these can be variables or pointers or members of other structs.  
	//wndclassex madhe 12 memberach ahet and wndclass madhe 10.cbSize and hIconSm antar add zale.
	wndclass.cbSize = sizeof(WNDCLASSEX);//cb=count of bites. Hya structure the size kiti ahe in bytes.
	wndclass.style = CS_HREDRAW | CS_VREDRAW;//macro associating of unsigned int. Here v=vertical and h=horizontal. Hya prakara chi window chi style kashi ahe. Bhint horizontally and vertically paint kar. CS=class style
	wndclass.cbClsExtra = 0;//is there any extra information about this window's class(prakar) in terms of bytes.cls->class. Nahi mhanun 0.
	wndclass.cbWndExtra = 0;//is there any extra information about the specific windows that are going to be created.Now is there any extra information of these created windows in terms of bytes. Nahi mhanun 0
	wndclass.lpfnWndProc = WndProc;//here we are not calling but giving an address of WndProc to wndclass.lpfnWndProc is the address of your windows callback funcction.
	wndclass.lpszClassName = szClassName; 
	wndclass.lpszMenuName = NULL;//AS it is a simple code, we do not have a menu so NULL.Here NULL means nothing or 0.

	//First Function Call of Win32 APILibrary of gdi32
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//hbr=handle to brush for window bg. It is read as handle to brush which colors the bg of the window.GetStockObject la call kela ahe to get the object from our stock.Tyala parameter WHITE_BRUSH pass kelay and return type typecast kartoy HBRUSH madhe ani thevtoy hbrBackground. GetStockObject tumhala gdi object deto. So tya kada brush sodun azun bharpur kahi goshti astat:font(HFONT),pen(HPEN) and brush.GetStockObject return type is HGDIOBJ
	wndclass.hInstance = hInstance;//ha window cha class jo ahe to hya process cha ahe tya process cha instance handle kay ahe.
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);//cursor load karava lagto as toh resource ahe. exe file jashi ram madhe odhli jaate tashich cursor chi ek file aste having .cur extension.LoadCursor cha pahila parameter pahila pparameter hys process chya kuthlya instance saathi cursor ahe mhanjech pahila parameter cha type hInstance.We have passe Null over here as we are saying that we have a simple window class and maza jo default instance ahe toch consider kar. And if write NULL, it means that we do not have to load any .cur file and the type of cursor from that file. Tya mule apan hInstance astana sudha apan pahila parameter NULL pass karto.IDC_ARROW means ID of default cursor which is an arrow. Here NULL means to consider the default value. Hyacha return type hCursor ahe.
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//id of icon. and return type hIcon ahe.
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);//sm=small icon. comes into explorer.

	//Register the above Window class
	RegisterClassEx(&wndclass);//here we register the window cha prakharto the OS.Register by window Class jyat 12 members detoy and OS register kartoy.RegisterClassEx cha return type ahe ATOM. He ek immutable string tayyar hoti and hi ATOM gheunach window register hote.

	//Create the window in memory. This creates windoe in your memory and not on our screen.
	hwnd = CreateWindow(szClassName, TEXT("Dnyanesh Milind Ujalambkar:First Window"), WS_OVERLAPPEDWINDOW,//tumchi window create karte and tya window la handle return karte, i.e, 32 bit unique unsigned int tya window la identify karayla hwnd variable madhe pakdun thevtoy.He apan hwnd madhe pakdun thevtoy.First parameter tells us that mi ji window tayyar karnar ahe tya window chya prakara cha naav kay ahe je apan szClassName variable mhanun kelay ani lpszClassName	la assign kelay OR what is the name of the wondow class whose windoe Create window is going to create.Second parameter caption bar text sangto OR window chya caption bar madhe kay text dakhvava.Third parameter tells us that WS->Window style. He sangta ki tumhi tumchyi widow kuthlya dusrya window var overlap karu shaktat kivha dusri window apla window var yeu shakte. WM_CREATE is recieved at this create window itself.Tgis call to create window sends W_CREATE msg to WndProc. 
		CW_USEDEFAULT,//Top left x coordinate. remember that the origin of our desktop is top left corner (0,0). ani apan saglyana default value set karu shakto.
		CW_USEDEFAULT,//Top left y coordinate.
		CW_USEDEFAULT,//width of window in pixels.
		CW_USEDEFAULT,//height of window in pixels.
		NULL,//is a macro. This means window chi parent kon ahe. This means that Create window la mahit nahi parent window kon ahe so desktop lack assume kar.Desktop hi OS chi window ahe.
		NULL,//mazya window cha menu cha handle kay ahe. Mazya window la kahich menu nahi ahe so tya mule NULL.
		hInstance,//hi window ji process dakhavti ahe tya windoe cha instance handle. 
		NULL);//is also a macro. Hya tayyar honarya window baddal kahi extra info sangaychi ahe ka. Null karan kahi nahi sangaychi ahe.

	//Show the window on the desktop. To show our window on screen we use ShowWindow. CreateWindow ni jo handle return kela ahe to apan jasa to tasa Show Window la deto.
	ShowWindow(hwnd, iCmdShow);//he vicharto ki kuthli window dakhvaych ahe. So apan sangto hwnd hya handle chi window mala show karaychi ahe.Ashi window ji program chi line gheun tayyar keli jaate.ashi multiple commands lihun window tayyar hoti te WinMain cha 4th parameter jasa sa tasa itha 2nd parameter mhanun pass kelay. iCmdShow chi default value SW_SHOWNORMAL/ SW mhanje show window ahe. Hya mule tumchi windows screen var diste.Hyach sobat azun 3 values astat hyache: SW_MAXIMIXE, SW_MINIMIZE and SW_HIDE.

	//Update/Paint the window on the desktop
	UpdateWindow(hwnd);

	//Message Loop: it is the heart of Win32 application.
	while (GetMessage(&msg, NULL, 0, 0))//GetMessage mhanje message queue madhna suck karna. Straw in our pic mhanje message queue. Te suck hotay &msg madhe.And apan toh kuthech vaparla nahi ahe so it is empty right now. Or it is not filled.So getmsg cha pahile parameter rikama mhanun jaatoy.Dusra is NULL: hwnd type. But aplya kade hwnd astana pan apan ka NULL pathavtoy? Getmsg chya aat message queue ahe. So tumchya window madhe message queue ahe and suck karna mhanje empty  msg madhe OS ni taklela parcel bharun application madhe odhna. Apan 2nd parameter NULL pass karat ahot because in case of advance WIN32 development, there could be cases where we have child windows as well.To recieve msgs of our window as well as our child windows, we pass it as NULL even when we have hwnd to [ass to it.So NULL is the default value.3rd and 4th parameters are 0: minimum and maximum limit of msg value resp.EG: if we had 3,8 with 10 msgs, then we are saying accept value from 3rd to 8th msgs only.
	{
		TranslateMessage(&msg);//kahi kahi veles msgs khup complex astat. So te soppe karnya saathi to msg translate karava lagtoy. That is our digestion of msg.
		DispatchMessage(&msg);//DispatchMessage is library function that has come from win 32 sdk tya code madhe asa bhaag ahe ki OS WndProc la call karte and DispatchMessage madhe WndProc la pathavla jaato je nantar te baghel kay karaycha ahe. So it is sending this simplified message from TranslateMessage() to WndProc()
	}

	return (int)msg.wParam;//return statement la kon ahe: jo msg madhe varti bharla ahe toch. return statament la msg jo asto toh msg WM_QUIT cha asto. And here wPrama=0. 
}//itha loop sampte mhanjech parat asa kalta program la ki kahi nahi parat straw laun basun raha. So it is called the 

//Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)//pahile parameter: kuthe click zala ahe he OS global hwnd table madhe map karte and te tya msg cha ball madhe pass karte. Dusra parameter: nakki msg kasa ahe: Left button click: WM_LBUTTONDOWNl;Right button click: WM_RBUTTONDOWN;Key down: WM_KEYDOWN. All these are macros having unsigned int valed. So left click asel tar te jata hya second parameter. So all window are UINT type.Msg struct che pahile 4 members he WndProc che 4 parameters ahet.So he 4 members parameters mhanun pass hoto WndProc madhe.
{

	//Variable Declarations:
	TCHAR str[255];
	wchar_t ch;
	int x, y;
	//code
	switch (iMsg)//all windows msgs are macros. In our window procedure function, the switch is put on our incoming message.
	{
	case WM_CREATE:
		wsprintf(str, TEXT("WM_CREATE MESSAGE IS RECIEVED"));
		MessageBox(NULL, TEXT("WM_CREATE MESSAGE IS RECIEVED"), TEXT("MESSAGE"), MB_OK);
		break;

	case WM_KEYDOWN:
		switch (LOWORD(wParam))
		{
		case VK_ESCAPE:
			DestroyWindow(hwnd);
		}
		/*wsprintf(str, TEXT("WM_KEYDOWN MESSAGE IS RECIEVED"));
		MessageBox(NULL, str, TEXT("MESSAGE"), MB_OK);//MessageBox is window. First parameter vicharta ki hya window cha parent window cha naav kay ahe.NULL mhanje Desktop will become parent. 2nd parameter is UNOCPDE string that we want to show. 3rd parameter msg box chya caption madhe kay disla pahijel. 4th parameter message box chi property sangta. Aplyala fakt ok dakhvaychay mhanun hech. MB_YES,MB_NO,MB_ABORT etc.*/
		break;

	case WM_CHAR:
		ch = wParam;
		wsprintf(str, TEXT("WM_CHAR MESSAGE IS RECIEVED for character %c"), ch);
		MessageBox(NULL, str, TEXT("MESSAGE"), MB_OK);//MessageBox is window. First parameter vicharta ki hya window cha parent window cha naav kay ahe.NULL mhanje Desktop will become parent. 2nd parameter is UNOCPDE string that we want to show. 3rd parameter msg box chya caption madhe kay disla pahijel. 4th parameter message box chi property sangta. Aplyala fakt ok dakhvaychay mhanun hech. MB_YES,MB_NO,MB_ABORT etc.
		break;

	case WM_LBUTTONDOWN: 
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		wsprintf(str, TEXT("WM_LBUTTONDOWN MESSAGE IS RECIEVED AT (%d,%d)"),x, y);
		MessageBox(NULL, str, TEXT("MESSAGE"), MB_OK);
		break;

	case WM_RBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		wsprintf(str, TEXT("WM_RBUTTONDOWN MESSAGE IS RECIEVED AT (%d,%d)"),x, y);
		MessageBox(NULL, str, TEXT("MESSAGE"), MB_OK);
		break;
	
	case WM_DESTROY://case can only be used with integer or character constants. So WM_DESTROY is a macro and not a struct.WM=window message. Also WM_DESTORY he window saathi and WM_QUIT he akhya application saathi ahe.
		wsprintf(str, TEXT("WM_DSETROY MESSAGE IS RECIEVED"));
		MessageBox(NULL, str, TEXT("MESSAGE"), MB_OK);
		PostQuitMessage(0);//Azun ek swata cha msg cha ball tayyar karun pool madhe takto of WM_QUIT.Tyacha wParam=0 asto and lParam=0.
		break;
	default: 
		break;
	}

	//Calling default Window Procedure
	return DefWindowProc(hwnd, iMsg, wParam, lParam);//DefWindowProc returns LRESULT type of value that passes to WNDProc and returns as its value. Default Window procedure.Is there any extra information is expressed by wParam and Lparam. Coordinate where the actual click happens: (x,y) and system time. These are the 6 members of the parcel in the message pool.
}

