#include<Windows.h>
#include<mmsystem.h>//mm stands for multimedia.We are including this for playsound() API.
#include "Window.h"
//Import Library(instead of writing its name in link.exe command line.
#pragma comment(lib,"winmm.lib")//winmm.lib is the library of play sound.

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
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);//hbr=handle to brush for window bg. It is read as handle to brush which colors the bg of the window.GetStockObject la call kela ahe to get the object from our stock.Tyala parameter WHITE_BRUSH pass kelay and return type typecast kartoy HBRUSH madhe ani thevtoy hbrBackground. GetStockObject tumhala gdi object deto. So tya kada brush sodun azun bharpur kahi goshti astat:font(HFONT),pen(HPEN) and brush.GetStockObject return type is HGDIOBJ
	wndclass.hInstance = hInstance;//ha window cha class jo ahe to hya process cha ahe tya process cha instance handle kay ahe.
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);//cursor load karava lagto as toh resource ahe. exe file jashi ram madhe odhli jaate tashich cursor chi ek file aste having .cur extension.LoadCursor cha pahila parameter pahila pparameter hys process chya kuthlya instance saathi cursor ahe mhanjech pahila parameter cha type hInstance.We have passe Null over here as we are saying that we have a simple window class and maza jo default instance ahe toch consider kar. And if write NULL, it means that we do not have to load any .cur file and the type of cursor from that file. Tya mule apan hInstance astana sudha apan pahila parameter NULL pass karto.IDC_ARROW means ID of default cursor which is an arrow. Here NULL means to consider the default value. Hyacha return type hCursor ahe.
	wndclass.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(DMU_ICON));//id of icon. and return type hIcon ahe.
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(DMU_ICON));//sm=small icon. comes into explorer.

	//Register the above Window class
	RegisterClassEx(&wndclass);//here we register the window cha prakharto the OS.Register by window Class jyat 12 members detoy and OS register kartoy.RegisterClassEx cha return type ahe ATOM. He ek immutable string tayyar hoti and hi ATOM gheunach window register hote.

	//Create the window in memory. This creates windoe in your memory and not on our screen.
	hwnd = CreateWindow(szClassName, TEXT("Dnyanesh Milind Ujalambkar:First Window"), WS_OVERLAPPEDWINDOW,//tumchi window create karte and tya window la handle return karte, i.e, 32 bit unique unsigned int tya window la identify karayla hwnd variable madhe pakdun thevtoy.He apan hwnd madhe pakdun thevtoy.First parameter tells us that mi ji window tayyar karnar ahe tya window chya prakara cha naav kay ahe je apan szClassName variable mhanun kelay ani lpszClassName	la assign kelay OR what is the name of the wondow class whose windoe Create window is going to create.Second parameter caption bar text sangto OR window chya caption bar madhe kay text dakhvava.Third parameter tells us that WS->Window style. He sangta ki tumhi tumchyi widow kuthlya dusrya window var overlap karu shaktat kivha dusri window apla window var yeu shakte.
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

	//Variable Declarations
	HDC hdc = NULL;
	PAINTSTRUCT ps;//this is static as we are using it for WM_PAINT as well as WM_CREATE.Paint struct 6 membeers astat: 3 reserved for OS. 3 apan vapru shakto.Ani he sagle milalya nanter painter pohochla.
	RECT rect;//this is also a struct this is static as we are using it for WM_PAINT as well as WM_CREATE. It has 4 parameters in this struct: refer image.
	HBRUSH hBrush = NULL;
	static int iPaintFlag = 0; //we declare it as static as it should retain its value across WM_CHAR and WM_PAINT.	

	//code
	switch (iMsg)//all windows msgs are macros
	{
	case WM_CREATE://zar tumhala application suru zalya zalya kahi vhyacha OR initialisation asel tar this is the best place to showcase it. 
		ZeroMemory((void*)&ps, sizeof(PAINTSTRUCT));
		ZeroMemory((void*)&rect, sizeof(RECT));

		//Begin playing the music
		PlaySound(MAKEINTRESOURCE(DMU_MUSIC), GetModuleHandle(NULL), SND_ASYNC | SND_LOOP | SND_RESOURCE);//1st parameter: which resource.2nd parameter: kuthna ghyaycha haan resource?:aplyach process madhna ghyaycha,i.e, exe ahe mhanun NULL. Otherwise jya process madhun gheto tya path cha exe paste karaycha.Instance(global)=Module.3rd parameter: SouND. so music sagle asynchronously play hu de.SND_LOOP mhanje he music loop madhe asu de.SND_RESOURCE mhanje maza sound resource madhun ghe.
		//Setting timer DMU_TIMER 201
		SetTimer(hwnd, DMU_TIMER, 1000, NULL);//1st parameter: kuthlya window saathi?. 2nd parameter: kuthla timer set karu?3rd parameter: kiti time saathi?:in miliseconds.4th parameter:NULL apan 2 jaga ahet: either WndProc or 4th itha call karava lagto.firstly its type is TIMERPROC meaning timer procedure.It is a callback that the OS calls once our specified time specified in the 3rd parameter is over. However, we are going to handle TIMERPROC in WndProc itself, thus we are specifying it as NULL.
		break;

	case WM_PAINT://fakt painting related code asla pahijel itha.He sagle aple 8 cases madhe yenar ahet je apan lijla ahet.
		GetClientRect(hwnd, &rect);//get the client area rectangle of our window.First parameter kuthlya window cha handle: tya window cha unique 32 bit mhanjech hwnd. Dusra parameter: rect madhe de.Refer image for this.Get client area rectangle for our window.Tyacha kahi asa direct connection nahi ahe painting sobat. Hyachya nantar saglech hdc la handle kartet kivha return kartaet. One or the these 2. 

		hdc = BeginPaint(hwnd, &ps);//hwnd=aplya window cha unique id jo paint karaycha ahe.ps=rikama paint struct patahv je window che chotyatlya chota window cha rectangle mi kasa paint karto.get the painter hdc to do painting work for our window.
		switch (iPaintFlag)
		{
		case 1:
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			break;
		case 2:
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			break;
		case 3:
			hBrush = CreateSolidBrush(RGB(0, 0, 255));
			break;
		case 4:
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			break;
		case 5:
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			break;
		case 6:
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			break;
		case 7:
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			break;
		case 8:
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			break;
		default:
			//Create a grey colored brush
			hBrush = CreateSolidBrush(RGB(128, 128, 128));
			break;
		}

		//Give the brush to the painter
		SelectObject(hdc, hBrush);//pahila parameter: kuthlya painter la he dyaycha. 2nd parameter: kay dyaycha ahe? Varti dilela hBrush.
		
		//Fill our client area rectangle with the color of the selected brush.
		FillRect(hdc, &rect,hBrush);//pahila parameter: koni bhint bharaycha.2nd parameter: kuthla area?. Haan handle GetClientRect chya 2nd pareter madhna ala ahe.3rd parameter: kashani rangvu? Varti select kelela selected brush
		
		//Release the brush
		if (hBrush != NULL)//bhande kharakti zali
		{
			DeleteObject(hBrush);//j1 vadhla
			hBrush = NULL;//Bhande dhutli
		}

		if (hdc !=NULL)
		{
			EndPaint(hwnd, &ps);
			hdc = NULL;
		}
		EndPaint(hwnd, &ps);//release the painter hdc once the painting work is d1. hdc is opaque pointer ahe pan tari apla la sangava lagta ki tyala memory allocation free kar.Ji memory mala Beginpaint ni milven dili ti atta release kar.
		break;

	case WM_TIMER:
		//Kill the timer DMU_TIMER 
		KillTimer(hwnd, DMU_TIMER);//Parameter he SetTimer che pahile 2 parameters ahet.
		iPaintFlag++;
		InvalidateRect(hwnd, NULL, TRUE);
		if (iPaintFlag > 8)
		{
			iPaintFlag = 0; 
		}
		//Setting timer DMU_TIMER 201
		SetTimer(hwnd, DMU_TIMER, 1000, NULL);//this is supposed to keep our loop running continuosly due to which our colors change automatically and not stop after the first color change from grey to red.
		break;

	case WM_DESTROY://case can only be used with integer or character constants. So WM_DESTROY is a macro and not a struct.WM=window message. Also WM_DESTORY he window saathi and WM_QUIT he akhya application saathi ahe. This is the best place to uninitialise something.
		PlaySound(NULL, 0, 0);
		PostQuitMessage(0);//Azun ek swata cha msg cha ball tayyar karun pool madhe takto of WM_QUIT.Tyacha wParam=0 asto and lParam=0.This shouls always be the last line of WM_DESTROY.
		break;
	default: 
		break;
	}

	//Calling default Window Procedure
	return DefWindowProc(hwnd, iMsg, wParam, lParam);//DefWindowProc returns LRESULT type of value that passes to WNDProc and returns as its value. Default Window procedure.Is there any extra information is expressed by wParam and Lparam. Coordinate where the actual click happens: (x,y) and system time. These are the 6 members of the parcel in the message pool.
}

