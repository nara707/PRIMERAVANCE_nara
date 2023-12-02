// PRIMERAVANCE_nara.cpp : Define el punto de entrada de la aplicación.
//

#include "framework.h"
#include "PRIMERAVANCE_nara.h"
#include "framework.h"
#include <string>
#include <commctrl.h>
#include <commdlg.h>
#include <map>
#include <vector>
#include<windows.h>
#include <fstream> 

#define MAX_LOADSTRING 100
#define IDC_TIMER1 1000

using namespace std;

HWND hWnd = nullptr;

//struct NODOLA {
//    CITA* dato;
//    NODOLA* siguiente;
//};
//struct CITAS {
//    NODOLA* origen;
//    NODOLA* fin;
//}LISTACITAS;
// Variables globales:
struct DOCTOR {
    DOCTOR* ante;
    WCHAR nom[100];
    WCHAR contra[100];
    WCHAR ced[100];
    WCHAR us[15];
    /*CITA* CITAS; */
    DOCTOR* sig;
    /*DOCTOR() : CITAS(nullptr) {} */
};

struct CITAS {
    CITAS* ante;
    WCHAR cliente[100];
    WCHAR masc[100];
    WCHAR tel[100];
    WCHAR motivo[100];
    WCHAR precio[100];
    WCHAR year[100];
    WCHAR month[100];
    WCHAR day[100];
    WCHAR hora[100];
    WCHAR mn[100];
    WCHAR seg[100];
    DOCTOR* doctorAsociado;
    CITAS* sig;

    CITAS() : doctorAsociado(nullptr), ante(nullptr),  sig(nullptr) {
        cliente[0] = L'\0';
        masc[0] = L'\0';
        motivo[0] = L'\0';
        tel[0] = L'\0';
        precio[0] = L'\0';
        year[0] = L'\0';
        month[0] = L'\0';
        day[0] = L'\0';
        hora[0] = L'\0';
        mn[0] = L'\0';
        seg[0] = L'\0';
    }
};
struct Cerrar {
    DOCTOR doctor;
    CITAS citas;
};

struct especie {
    especie* ante;
    WCHAR ESP[100];
    especie* sig;
}/*lista_especie*/; 

struct NODO_DOCTOR {
    DOCTOR* dato;
    NODO_DOCTOR* siguiente;
    NODO_DOCTOR* ante;
};

struct LISTA_DOCTORES {
    NODO_DOCTOR* origen;
    NODO_DOCTOR* fin;
};

struct NODO_especie {
    especie* dato;
    NODO_especie* siguiente;
    NODO_especie* ante;
};

struct NODO_CITA {
    CITAS* dato;
    NODO_CITA* siguiente;
    NODO_CITA* ante;
};

struct LISTA_CITAS {
    NODO_CITA* origen;
    NODO_CITA* fin;
};

struct lista_especie {
    NODO_especie* origen;
    NODO_especie* fin; 

};

// Uso de las estructuras
lista_especie lista_especies;
LISTA_DOCTORES listaDoctores;
NODO_DOCTOR* loggeado = NULL;
LISTA_CITAS listaCitas;
NODO_especie* logesp = NULL;

map<wstring, DOCTOR> doctores;
map<wstring, DOCTOR> agendaDoctores;
#define IDC_TIMER1 1000
HINSTANCE hInst;                                // instancia actual
WCHAR szTitle[MAX_LOADSTRING];                  // Texto de la barra de título
WCHAR szWindowClass[MAX_LOADSTRING];            // nombre de clase de la ventana principal

// Declaraciones de funciones adelantadas incluidas en este módulo de código:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
//LRESULT CALLBACK    PrincipalCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK AGENDACallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK REGISTROCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK LOGCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK VENTANACITACallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK VENTANAESPECIECallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); 
LRESULT CALLBACK MODIFICARCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
bool menu(int opcion, HWND ventana);  
void eliminarListaCitas(LISTA_CITAS* listaCitas);
void eliminarListaDoctores(LISTA_DOCTORES* listaDoctores);
DOCTOR* crearDoctor(WCHAR* us, WCHAR* contra, WCHAR* nom, WCHAR* ced);
especie* crearespecie(WCHAR* ESP);
CITAS* crearCita(WCHAR* cliente, WCHAR* masc, WCHAR* motivo, WCHAR* tel, WCHAR* precio, WCHAR* year, WCHAR* month, WCHAR* day, WCHAR* hora, WCHAR* mn, WCHAR* seg);
NODO_DOCTOR* nuevoNodo(DOCTOR* dato);
NODO_CITA* nuevoNodo(CITAS* dato);
NODO_especie* nuevoNodo(especie* dato);
NODO_DOCTOR* buscarUsuario(LISTA_DOCTORES* listaDoctores, WCHAR* buscar);
NODO_CITA* buscarCita(LISTA_CITAS* listaCitas, WCHAR* buscar);
NODO_especie* buscarespecie(lista_especie* listaespecies, WCHAR* buscar);
NODO_DOCTOR* buscarDoctorPorUsuario(WCHAR* buscar);
NODO_CITA* buscarCitaPorCliente(WCHAR* buscar);
void agregarDoctorInicio(DOCTOR* dato);
void agregarDoctorFinal(DOCTOR* dato);
void agregarespecieFinal(especie* dato);
void agregarDoctorEnMedio(WCHAR* buscar, DOCTOR* dato);
void agregarCitaInicio(CITAS* dato);
void agregarCitaFinal(CITAS* dato);
void agregarCitaEnMedio(WCHAR* buscar, CITAS* dato);
void CerrarPrograma(HWND hWnd); 
DOCTOR* obtenerDoctorSesion(const wstring& us);
bool guardarDoctorEnArchivo(const DOCTOR& doctor);
bool guardarCitaEnArchivo(const CITAS& cita);


//NODO_DOCTOR* buscarDoctorPorUsuario(WCHAR* buscar);
//void g_hSelectedImage();
HBITMAP g_hSelectedImage = nullptr; 

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Colocar código aquí.
    /*struct LISTA_CITAS {
        NODO_CITA* origen;
        NODO_CITA* fin;
    }; */



    // Inicializar cadenas globales
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PRIMERAVANCENARA, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Realizar la inicialización de la aplicación:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PRIMERAVANCENARA));

    MSG msg;

    // Bucle principal de mensajes:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    /*eliminarListaCitas(LISTA_CITAS * listaCitas);
    eliminarListaDoctores();
   */
    /*CerrarPrograma(hWnd); */
    return (int)msg.wParam;
}



//
//  FUNCIÓN: MyRegisterClass()
//
//  PROPÓSITO: Registra la clase de ventana.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PRIMERAVANCENARA));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PRIMERAVANCENARA);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCIÓN: InitInstance(HINSTANCE, int)
//
//   PROPÓSITO: Guarda el identificador de instancia y crea la ventana principal
//
//   COMENTARIOS:
//
//        En esta función, se guarda el identificador de instancia en una variable común y
//        se crea y muestra la ventana principal del programa.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Almacenar identificador de instancia en una variable global

    HWND hWnd = CreateDialog(hInst, MAKEINTRESOURCE(INICIO_SES), NULL, WndProc);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}



/* FUNCIÓN: WndProc(HWND, UINT, WPARAM, LPARAM)

 PROPÓSITO: Procesa mensajes de la ventana principal.

 WM_COMMAND  - procesar el menú de aplicaciones
 WM_PAINT    - Pintar la ventana principal
 WM_DESTROY  - publicar un mensaje de salida y volver*/


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Analizar las selecciones de menú:
        switch (wmId) {

        case INICIO: {

            WCHAR us[100] = { 0 };
            GetDlgItemText(hWnd, IDC_USUARIO, us, 100);

            WCHAR contra[100] = { 0 };
            GetDlgItemText(hWnd, IDC_CONTRA, contra, 100);

            NODO_DOCTOR* nodoDoctor = buscarDoctorPorUsuario(us); 

            if (nodoDoctor != nullptr) {
                if (wcscmp(nodoDoctor->dato->us, us) == 0 && wcscmp(nodoDoctor->dato->contra, contra) == 0) { 
                    // Las credenciales son correctas
                    loggeado = nodoDoctor;
                    HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(AGENDA), NULL, AGENDACallback);
                    ShowWindow(ventana, SW_SHOW);
                    EndDialog(hWnd, 0);
                    /*MessageBox(hWnd, L"Inicio de sesión exitoso", L"Éxito", MB_OK | MB_ICONINFORMATION)*/
                }
                else {
                    // Contraseña incorrecta
                    int respuesta = MessageBox(hWnd, L"Usuario o contrase\u00F1a incorrecta", L"Error", 0 | MB_ICONASTERISK);

                }
            
            }
            else {
                // Usuario no encontrado
                int respuesta = MessageBox(hWnd, L"INCORRECTO", L"Error", 0| MB_ICONQUESTION);
                //if (respuesta == MB_OKCANCEL) {
                //    //EndDialog(hWnd, 0);
                //}
            }
        }break;
        case REGIS: {
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(REGISTRO), NULL, REGISTROCallback);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }break;

        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDC_EXIT:  
            DestroyWindow(hWnd); 
            break;

        //case WM_CLOSE: 
        //    // En el mensaje de cierre de ventana, llamar a la función de cierre seguro
        //    CerrarPrograma(hWnd); 
        //    break; 

            //default:
            //    return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Agregar cualquier código de dibujo que use hDC aquí...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);  
        break;
        //default:
        //    return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Controlador de mensajes del cuadro Acerca de.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

LRESULT CALLBACK AGENDACallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) 
    {
    case WM_INITDIALOG: 
    {
        SetDlgItemText(hWnd, IDC_NOMAGEN, loggeado->dato->nom);  
        if (g_hSelectedImage != nullptr)
        {
            SendMessage(GetDlgItem(hWnd, IDC_FOTOAGEN), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)g_hSelectedImage);
        }

    } break;

    case WM_COMMAND: 
    {

        int wmId = LOWORD(wParam);
        int wmEvent = HIWORD(wParam);
        if (menu(wmId, hWnd)) 
        {
            return FALSE;
        }
        switch (wmId) 
        {
        case AGENDAR: 
        {
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(CITA), NULL, VENTANACITACallback);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0); 
        } break;
        case IDC_MOD: {
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(MODIFICAR), NULL, MODIFICARCallback);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }break;
        case IDM_EXIT: 
            DestroyWindow(hWnd); 
            break; 
        }

        //default:
        //    return DefWindowProc(hWnd, message, wParam, lParam); 
    }break;
    //case WM_CLOSE:
    //    // En el mensaje de cierre de ventana, llamar a la función de cierre seguro
    //    CerrarPrograma(hWnd);
    //    break;

    case WM_DESTROY: 
        PostQuitMessage(0);
        break; 
    }

    return FALSE;
}

LRESULT CALLBACK VENTANACITACallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message) 
    {

    case WM_INITDIALOG: 
    {  
        /*NODO_CITA* logged = listaCitas.origen;
        while (loggeado != NULL) {
            SendMessage(GetDlgItem(hwnd, IDC))
        }
        SetDlgItemText(hWnd, IDC_NOMCITA, loggeado->dato->nom); */
        NODO_especie* nodoActual = lista_especies.origen;

        if (g_hSelectedImage != nullptr)
        {
            SendMessage(GetDlgItem(hWnd, FOTOC), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)g_hSelectedImage); 
        }
        HWND hListBox = GetDlgItem(hWnd, IDC_ESPECIE);
        while(nodoActual != nullptr) {
            especie* logesp = nodoActual->dato; 
            
            SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)logesp->ESP); 
            nodoActual = nodoActual->siguiente; 

        }
  
        
        SendMessage(GetDlgItem(hWnd, IDC_ESTADO), CB_INSERTSTRING, 0, (LPARAM)L"PENDIENTE"); 
        SendMessage(GetDlgItem(hWnd, IDC_ESTADO), CB_INSERTSTRING, 0, (LPARAM)L"CONFIRMADA"); 
        SendMessage(GetDlgItem(hWnd, IDC_ESTADO), CB_INSERTSTRING, 0, (LPARAM)L"CANCELADA"); 
        SendMessage(GetDlgItem(hWnd, IDC_ESTADO), CB_INSERTSTRING, 0, (LPARAM)L"REPROPGRAMADA");

        SendMessage(GetDlgItem(hWnd, IDC_ESPECIE), CB_INSERTSTRING, 0, (LPARAM)L"PERRO(Canis lupus familiaris)");
        SendMessage(GetDlgItem(hWnd, IDC_ESPECIE), CB_INSERTSTRING, 0, (LPARAM)L"GATO(Felis catus)");
        SendMessage(GetDlgItem(hWnd, IDC_ESPECIE), CB_INSERTSTRING, 0, (LPARAM)L"PEZ");
        SendMessage(GetDlgItem(hWnd, IDC_ESPECIE), CB_INSERTSTRING, 0, (LPARAM)L"HAMSTER(cricetinae)");
        SendMessage(GetDlgItem(hWnd, IDC_ESPECIE), CB_INSERTSTRING, 0, (LPARAM)L"PAJARO(ave)");

        

    }break;

    case WM_COMMAND: 
    {
        int id = LOWORD(wParam);
        if (menu(id, hWnd)) 
        {
            return FALSE;
        }
        switch (id) 
        {
        case IDCANCEL: 
        {
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(AGENDA), NULL, AGENDACallback);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }break;

        case ACEPTAR: 
        {

            WCHAR cliente[100] = { 0 };
            GetDlgItemText(hWnd, IDC_NOM, cliente, 100);

            WCHAR mascota[100] = { 0 };
            GetDlgItemText(hWnd, IDC_MASC, mascota, 100);

            WCHAR motivo[100] = { 0 };
            GetDlgItemText(hWnd, IDC_MOT, motivo, 100);

            WCHAR tel[100] = { 0 };
            GetDlgItemText(hWnd, IDC_MOT, tel, 100);

            WCHAR precio[100] = { 0 };
            GetDlgItemText(hWnd, IDC_MOT, precio, 100);

            WCHAR day[100] = { 0 };
            GetDlgItemText(hWnd, IDC_MOT, day, 100);

            WCHAR month[100] = { 0 };
            GetDlgItemText(hWnd, IDC_MOT, month, 100);

            WCHAR year[100] = { 0 };
            GetDlgItemText(hWnd, IDC_MOT, year, 100);

            WCHAR hora[100] = { 0 };
            GetDlgItemText(hWnd, IDC_MOT, hora, 100);

            WCHAR seg[100] = { 0 };
            GetDlgItemText(hWnd, IDC_MOT, seg, 100);

            
            WCHAR mn[100] = { 0 };
            GetDlgItemText(hWnd, IDC_MOT, mn, 100);

           /* int telefono = GetDlgItemInt(hWnd, IDC_TEL, NULL, FALSE);

            SYSTEMTIME date = { 0 };
            HWND datepicker = GetDlgItem(hWnd, IDC_DATETIMEPICKER1);
            DateTime_GetSystemtime(datepicker, &date);
            int year = date.wYear;
            int month = date.wMonth;
            int day = date.wDay;*/


            /*SYSTEMTIME time = { 0 };
            HWND timepicker = GetDlgItem(hWnd, IDC_DATETIMEPICKER2);
            DateTime_GetSystemtime(timepicker, &time);
            int hora = time.wHour;
            int mn = time.wMinute;
            int seg = time.wSecond;*/



            //WCHAR precioStr[255] = { 0 };
            //GetDlgItemText(hWnd, IDC_COST, precioStr, 255);
            //float precio = 0.0f;
            //swscanf_s(precioStr, L"%f", &precio);


            agregarCitaFinal(crearCita(cliente, mascota, motivo, tel, precio, year, month, day, hora, mn, seg));
            MessageBox(hWnd, L"CITA", L"CITA GUARDADA >.O", MB_OK|MB_ICONHAND);
           
        }break;
        
        case ADD: 
        {
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(ESPECIE), NULL, VENTANAESPECIECallback);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }break;

        /*case IDM_EXIT:   
            DestroyWindow(hWnd);  
            break; */

        }
    }break;
    case WM_CLOSE:{
        CerrarPrograma(hWnd);
        EndDialog(hWnd, 0);
    }break;

    case WM_DESTROY:
        PostQuitMessage(0); 
        break;
        //default:
        //    return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return FALSE;
}

LRESULT CALLBACK REGISTROCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        if (menu(wmId, hWnd)) { 
            return FALSE;
        }
        switch (wmId) {

        case IDC_BUSCAR: {
            WCHAR ruta[300] = { 0 };
            OPENFILENAME ofn;
            ZeroMemory(&ofn, sizeof(ofn));
            char cDirFile[MAX_PATH] = "";


            ofn.lStructSize = sizeof(OPENFILENAME);
            ofn.hwndOwner = hWnd;
            ofn.lpstrFile = ruta;
            ofn.nMaxFile = MAX_PATH;
            ofn.lpstrFilter = L"lol\0*.bmp\0Todos\0*.*";
            ofn.nFilterIndex = 1;
            ofn.lpstrTitle = NULL;
            ofn.nMaxFileTitle = 0;
            ofn.lpstrInitialDir = NULL;
            ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
            if (GetOpenFileName(&ofn)) {
                g_hSelectedImage = (HBITMAP)LoadImage(
                    hInst,
                    ruta,
                    IMAGE_BITMAP,
                    150, 150,
                    LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);

                if (g_hSelectedImage != NULL) {
                    SendMessage(
                        GetDlgItem(hWnd, IDC_FOTO),
                        STM_SETIMAGE,
                        IMAGE_BITMAP,
                        (LPARAM)g_hSelectedImage);
                }
            }
        }break;



        case IDOK: {
            WCHAR nom[255] = { 0 };
            GetDlgItemText(hWnd, IDC_EDIT1, nom, 255);

            WCHAR contra[255] = { 0 };
            GetDlgItemText(hWnd, IDC_EDIT2, contra, 255);

            WCHAR ced[255] = { 0 };
            GetDlgItemText(hWnd, IDC_EDIT4, ced, 255);

            WCHAR us[255] = { 0 };
            GetDlgItemText(hWnd, IDC_EDIT5, us, 255);
            if (wcscmp(nom, L"") == 0 || wcscmp(contra, L"") == 0 || wcscmp(ced, L"") == 0 || wcscmp(us, L"") == 0) {
                MessageBox(hWnd, L"INCOMPLETO", L"registro incompleto", 0 | MB_ICONEXCLAMATION);

            }
            else {
                agregarDoctorFinal(crearDoctor(us, contra, nom, ced));
                MessageBox(hWnd, L"REGISTRO COMPLETO ", L"COMPLETO", 0);
                HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(INICIO_SES), NULL, WndProc);
                ShowWindow(ventana, SW_SHOW);
                EndDialog(hWnd, 0);
            }
        }break;
        case RETORNO: {
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(INICIO_SES), NULL, WndProc);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }break;
        case IDM_EXIT: 
            DestroyWindow(hWnd); 
            break; 
        }
    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
        //default:
        //    return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return FALSE;
}
LRESULT CALLBACK LOGCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_INITDIALOG: {
        
        if (g_hSelectedImage != nullptr)
        {
            SendMessage(GetDlgItem(hWnd, IDC_FOTOPER), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)g_hSelectedImage);
        }
        /*SendMessage(hWnd, STM_SETIMAGE, IMAGE_BITMAP, (WPARAM)g_hSelectedImage); */
       
        SetDlgItemText(hWnd, IDC_EDIT_NOM_DOCTOR, loggeado->dato->nom);
        SetDlgItemText(hWnd, IDC_EDIT_CED_DOCTOR, loggeado->dato->ced);
        SetDlgItemText(hWnd, IDC_EDIT_CONTRA_DOCTOR, loggeado->dato->contra);
        SetDlgItemText(hWnd, IDC_EDIT_US_DOCTOR, loggeado->dato->us);
        /*SetDlgItem(hWnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)g_hSelectedImage);  */
        
    } break;
    case WM_COMMAND: {
        int wmId = LOWORD(wParam); 
        int wmEvent = HIWORD(wParam);  
        if (menu(wmId, hWnd)) {
            return FALSE;
        }
        switch (wmId) {

        case IDM_EXIT: { 
            DestroyWindow(hWnd); 
        }break;

        }
    }break;
    case WM_DESTROY: 
        PostQuitMessage(0); 
        break; 
        //default:

            //return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return FALSE;
}

LRESULT CALLBACK VENTANAESPECIECallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{

    switch (message) 
    {

    case WM_INITDIALOG: 
    {


    }break;

    case WM_COMMAND: 
    {

        int wmId = LOWORD(wParam);
        int wmEvent = HIWORD(wParam);
        if (menu(wmId, hWnd)) 
        {
            return FALSE;
        }
        switch (wmId) 
        {
        case IDCANCEL: 
        {
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(CITA), NULL, VENTANACITACallback);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }break;
        case AGREGAR_ES: 
        {
            WCHAR ESP[255];
            GetDlgItemText(hWnd, IDC_NUEVAESPECIE, ESP, 255);  

            agregarespecieFinal(crearespecie(ESP));

            SendMessage(
                GetDlgItem(hWnd, ESPECIESCOMBO),
                LB_ADDSTRING,
                0,
                reinterpret_cast<LPARAM>(ESP)
            );


        } break;





        case IDM_EXIT:
            DestroyWindow(hWnd);
        
            break;

        }
    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
        //default:
        //    return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return FALSE;
}

LRESULT CALLBACK MODIFICARCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message) {

    case WM_INITDIALOG: {

        if (g_hSelectedImage != nullptr)
        {
            SendMessage(GetDlgItem(hWnd, IDC_FOTOMOD), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)g_hSelectedImage);
        }

        SetDlgItemText(hWnd, IDC_NOMOD, loggeado->dato->nom); 

        SendMessage(GetDlgItem(hWnd, MODESPECIE), CB_INSERTSTRING, 0, (LPARAM)L"PERRO(Canis lupus familiaris)");
        SendMessage(GetDlgItem(hWnd, MODESPECIE), CB_INSERTSTRING, 0, (LPARAM)L"GATO(Felis catus)");
        SendMessage(GetDlgItem(hWnd, MODESPECIE), CB_INSERTSTRING, 0, (LPARAM)L"PEZ");
        SendMessage(GetDlgItem(hWnd, MODESPECIE), CB_INSERTSTRING, 0, (LPARAM)L"HAMSTER(cricetinae)");
        SendMessage(GetDlgItem(hWnd, MODESPECIE), CB_INSERTSTRING, 0, (LPARAM)L"PAJARO(ave)");



    }break;

    case WM_COMMAND: {

        int wmId = LOWORD(wParam);
        int wmEvent = HIWORD(wParam);
        if (menu(wmId, hWnd)) {
            return FALSE;
        }
        switch (wmId) {
        

            /*case OK: { 

                
            }break;*/

            case OK: {
                HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(AGENDA), NULL, AGENDACallback);
                ShowWindow(ventana, SW_SHOW);
                EndDialog(hWnd, 0);
            }break;
            case IDC_CANCELAR: { 
                HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(AGENDA), NULL, AGENDACallback);  
                ShowWindow(ventana, SW_SHOW); 
                EndDialog(hWnd, 0) ;
            }break;

            case IDM_EXIT:
                DestroyWindow(hWnd);
        
            break;

        }
    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
        //default:
        //    return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return FALSE;
}


bool menu(int opcion, HWND ventana) {   
    switch (opcion) {
    case ID_CITAS: {  
        HWND ventanaCitas = CreateDialog(hInst, MAKEINTRESOURCE(CITA), NULL, VENTANACITACallback);  
        ShowWindow(ventanaCitas, SW_SHOW);   
    } break;
    case ID_AGENDA: {
        HWND ventanaAgendas = CreateDialog(hInst, MAKEINTRESOURCE(AGENDA), NULL, AGENDACallback); 
        ShowWindow(ventanaAgendas, SW_SHOW); 
        
    } break;
    case ID_CUENTA: {
        HWND ventanaLogin = CreateDialog(hInst, MAKEINTRESOURCE(INF_DOC), NULL, LOGCallback); 
        ShowWindow(ventanaLogin, SW_SHOW);
        
    } break;
    case IDC_ESTADO: {  
       /* int res = MessageBox(hwnd, L"DESEA CERRAR EL PROGRAMA?", L"SALIR", MB_OKCANCEL | MB_ICONINFORMATION);
        if (res == IDOK)
        {
            f
        }*/
    } break;

    /*case IDM_EXIT: 
        DestroyWindow(hWnd); 
        break;*/ 

    default: return false;
    }
    return true; 
} 

void eliminarListaCitas(LISTA_CITAS* listaCitas) {
    NODO_CITA* actual = listaCitas->origen;
    NODO_CITA* siguiente = nullptr;

    while (actual != nullptr) {
        siguiente = actual->siguiente;
        delete actual->dato; // Liberar memoria del dato CITA
        delete actual;       // Liberar memoria del nodo NODO_CITA
        actual = siguiente;
    }

    // Reiniciar la lista, estableciendo origen y fin como nullptr
    listaCitas->origen = nullptr;
    listaCitas->fin = nullptr;
}
void eliminarListaDoctores(LISTA_DOCTORES* listaDoctores) {
    NODO_DOCTOR* actual = listaDoctores->origen;
    NODO_DOCTOR* siguiente = nullptr;

    while (actual != nullptr) {
        siguiente = actual->siguiente;
        delete actual->dato; // Liberar memoria del dato DOCTOR
        delete actual;       // Liberar memoria del nodo NODO_DOCTOR
        actual = siguiente;
    }

    // Reiniciar la lista, estableciendo origen y fin como nullptr
    listaDoctores->origen = nullptr;
    listaDoctores->fin = nullptr;
}
DOCTOR* crearDoctor(WCHAR* us, WCHAR* contra, WCHAR* nom, WCHAR* ced) {
    DOCTOR* nuevoDoctor = new DOCTOR();
    wcscpy_s(nuevoDoctor->nom, 100, nom);
    wcscpy_s(nuevoDoctor->contra, 100, contra);
    wcscpy_s(nuevoDoctor->us, 15, us);
    wcscpy_s(nuevoDoctor->ced, 100, ced);
    return nuevoDoctor;
}
CITAS* crearCita(WCHAR* cliente, WCHAR* masc, WCHAR* motivo, WCHAR* tel, WCHAR* precio, WCHAR* year, WCHAR* month, WCHAR* day, WCHAR* hora, WCHAR* mn, WCHAR* seg) {
    CITAS* nuevoCita = new CITAS();
    wcscpy_s(nuevoCita->cliente, 100, cliente);
    wcscpy_s(nuevoCita->masc, 100, masc);
    wcscpy_s(nuevoCita->motivo, 100, motivo);
    wcscpy_s(nuevoCita->tel, 100, tel);
    wcscpy_s(nuevoCita->precio, 100, precio);
    wcscpy_s(nuevoCita->year, 100, year);
    wcscpy_s(nuevoCita->day, 100, day);
    wcscpy_s(nuevoCita->month, 100, month); 
    wcscpy_s(nuevoCita->hora, 100, hora); 
    wcscpy_s(nuevoCita->mn, 100, mn);
    wcscpy_s(nuevoCita->seg, 100, seg); 


    

    return nuevoCita;
}
NODO_DOCTOR* nuevoNodo(DOCTOR* dato) {
    NODO_DOCTOR* nuevoNodoDoctor = new NODO_DOCTOR();
    nuevoNodoDoctor->dato = dato;
    nuevoNodoDoctor->siguiente = nullptr;
    nuevoNodoDoctor->ante = nullptr;

    return nuevoNodoDoctor;
}
NODO_especie* nuevoNodo(especie* dato) {
    NODO_especie* nuevoNodoespecie = new NODO_especie();
    nuevoNodoespecie->dato = dato;
    nuevoNodoespecie->siguiente = nullptr;
    nuevoNodoespecie->ante = nullptr;
    return nuevoNodoespecie;
}
NODO_CITA* nuevoNodo(CITAS* dato) {
    NODO_CITA* nuevoNodoCita = new NODO_CITA();
    nuevoNodoCita->dato = dato;
    nuevoNodoCita->siguiente = nullptr;
    nuevoNodoCita->ante = nullptr;

    return nuevoNodoCita;
}
NODO_especie* buscarespecie(lista_especie* listaespecies, WCHAR* buscar) {
    NODO_especie* actual = listaespecies->origen;
    while(actual != nullptr) {
        if (wcscmp(actual->dato->ESP, buscar) == 0) { 
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr; // No se encont)
}
NODO_DOCTOR* buscarUsuario(LISTA_DOCTORES* listaDoctores, WCHAR* buscar) { 
    NODO_DOCTOR* actual = listaDoctores->origen;

    while (actual != nullptr) {
        if (wcscmp(actual->dato->us, buscar) == 0) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr; // No se encontró el usuario
}
NODO_CITA* buscarCita(LISTA_CITAS* listaCitas, WCHAR* buscar) {
    NODO_CITA* actual = listaCitas->origen;

    while (actual != nullptr) {
        if (wcscmp(actual->dato->cliente, buscar) == 0) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr; // No se encontró la cita 
}


NODO_DOCTOR* buscarDoctorPorUsuario(WCHAR* buscar) {
    NODO_DOCTOR* actual = listaDoctores.origen;

    while (actual != nullptr) {
        if (wcscmp(actual->dato->us, buscar) == 0 || wcscmp(actual->dato->us, buscar) == 0) {
            return actual; // Se encontró el doctor, se devuelve el nodo correspondiente
        }
        actual = actual->siguiente;
    }

    return nullptr; // No se encontró el doctor en la lista
}
NODO_CITA* buscarCitaPorCliente(WCHAR* buscar) {
    NODO_CITA* actual = listaCitas.origen;

    while (actual != nullptr) {
        if (wcscmp(actual->dato->cliente, buscar) == 0) {
            return actual; // Se encontró el doctor, se devuelve el nodo correspondiente
        }
        actual = actual->siguiente;
    }

    return nullptr; // No se encontró el doctor en la lista
}
void agregarDoctorInicio(DOCTOR* dato) {
    NODO_DOCTOR* nuevoNodoDoctor = nuevoNodo(dato);

    if (listaDoctores.origen == nullptr) {
        listaDoctores.origen = nuevoNodoDoctor;
        listaDoctores.fin = nuevoNodoDoctor;
        nuevoNodoDoctor->siguiente = nullptr;
    }
    else {
        nuevoNodoDoctor->siguiente = listaDoctores.origen;
        listaDoctores.origen->ante = nuevoNodoDoctor;
        listaDoctores.origen = nuevoNodoDoctor;
    }
}

void agregarDoctorFinal(DOCTOR* dato) {
    NODO_DOCTOR* nuevoNodoDoctor = new NODO_DOCTOR();
    nuevoNodoDoctor->dato = dato;
    nuevoNodoDoctor->siguiente = nullptr;

    if (listaDoctores.origen == nullptr) {
        listaDoctores.origen = nuevoNodoDoctor;
        listaDoctores.fin = nuevoNodoDoctor;
        nuevoNodoDoctor->ante = nullptr;
    }
    else {
        nuevoNodoDoctor->ante = listaDoctores.fin;
        listaDoctores.fin->siguiente = nuevoNodoDoctor;
        listaDoctores.fin = nuevoNodoDoctor;
    }
}

void agregarDoctorEnMedio(WCHAR* buscar, DOCTOR* dato) {
    NODO_DOCTOR* busqueda = buscarDoctorPorUsuario(buscar);

    if (busqueda == nullptr) {
        return; // No se encontró el nodo de búsqueda, no se puede agregar en medio
    }

    NODO_DOCTOR* nuevoNodoDoctor = nuevoNodo(dato);
    nuevoNodoDoctor->siguiente = busqueda->siguiente;
    busqueda->siguiente = nuevoNodoDoctor;

    if (nuevoNodoDoctor->siguiente != nullptr) {
        nuevoNodoDoctor->siguiente->ante = nuevoNodoDoctor;
    }
    else {
        listaDoctores.fin = nuevoNodoDoctor; // Si se agregó al final, actualiza el fin 
    }
}

void agregarCitaInicio(CITAS* dato) {
    NODO_CITA* nuevoNodoCita = nuevoNodo(dato);

    if (listaCitas.origen == nullptr) {
        listaCitas.origen = nuevoNodoCita;
        listaCitas.fin = nuevoNodoCita;
        nuevoNodoCita->siguiente = nullptr;
    }
    else {
        nuevoNodoCita->siguiente = listaCitas.origen;
        listaCitas.origen->ante = nuevoNodoCita;
        listaCitas.origen = nuevoNodoCita;
    }
}

void agregarCitaFinal(CITAS* dato) {
    NODO_CITA* nuevoNodoCita = new NODO_CITA();
    nuevoNodoCita->dato = dato;
    nuevoNodoCita->siguiente = nullptr;

    if (listaCitas.origen == nullptr) {
        listaCitas.origen = nuevoNodoCita;
        listaCitas.fin = nuevoNodoCita;
        nuevoNodoCita->ante = nullptr;
    }
    else {
        nuevoNodoCita->ante = listaCitas.fin;
        listaCitas.fin->siguiente = nuevoNodoCita;
        listaCitas.fin = nuevoNodoCita;
    }
}

void agregarCitaEnMedio(WCHAR* buscar, CITAS* dato) {
    NODO_CITA* busqueda = buscarCitaPorCliente(buscar);

    if (busqueda == nullptr) {
        return; // No se encontró el nodo de búsqueda, no se puede agregar en medio
    }

    NODO_CITA* nuevoNodoCita = nuevoNodo(dato);
    nuevoNodoCita->siguiente = busqueda->siguiente;
    busqueda->siguiente = nuevoNodoCita;

    if (nuevoNodoCita->siguiente != nullptr) {
        nuevoNodoCita->siguiente->ante = nuevoNodoCita;
    }
    else {
        listaCitas.fin = nuevoNodoCita; // Si se agregó al final, actualiza el fin 
    }
}
DOCTOR* eliminarDoctorInicio() {
    if (listaDoctores.origen == nullptr)
        return nullptr;
    if (listaDoctores.origen == listaDoctores.fin)
        listaDoctores.fin = nullptr;
    NODO_DOCTOR* anterior = listaDoctores.origen;
    listaDoctores.origen = listaDoctores.origen->siguiente;
    DOCTOR* dato = anterior->dato;
    delete anterior;
    return dato;
}
DOCTOR* eliminarDoctorFinal() {
    if (listaDoctores.origen == nullptr)
        return nullptr;
    if (listaDoctores.origen == listaDoctores.fin)
        return eliminarDoctorInicio();

    NODO_DOCTOR* indice = listaDoctores.origen;
    while (indice != nullptr) {
        if (indice->siguiente == listaDoctores.fin) {
            break;
        }
        indice = indice->siguiente;
    }

    DOCTOR* dato = listaDoctores.fin->dato;
    delete listaDoctores.fin;
    listaDoctores.fin = indice;

    if (indice != nullptr)
        indice->siguiente = nullptr;

    return dato;
}
DOCTOR* eliminarDoctorEnMedio(WCHAR* buscar) {
    NODO_DOCTOR* busqueda = buscarDoctorPorUsuario(buscar);

    if (busqueda == nullptr)
        return nullptr;

    if (busqueda == listaDoctores.origen)
        return eliminarDoctorInicio();
    else if (busqueda == listaDoctores.fin)
        return eliminarDoctorFinal();

    NODO_DOCTOR* indice = listaDoctores.origen;
    while (indice != nullptr) {
        if (indice->siguiente == busqueda)
            break;
        indice = indice->siguiente;
    }

    DOCTOR* dato = busqueda->dato;
    if (indice != nullptr)
        indice->siguiente = busqueda->siguiente;

    delete busqueda;
    return dato;
}
CITAS* eliminarCitaInicio() {
    if (listaCitas.origen == nullptr)
        return nullptr;

    if (listaCitas.origen == listaCitas.fin)
        listaCitas.fin = nullptr;

    NODO_CITA* anterior = listaCitas.origen;
    listaCitas.origen = listaCitas.origen->siguiente;
    CITAS* dato = anterior->dato;
    delete anterior;
    return dato;
}

CITAS* eliminarCitaFinal() {
    if (listaCitas.origen == nullptr)
        return nullptr;

    if (listaCitas.origen == listaCitas.fin)
        return eliminarCitaInicio();

    NODO_CITA* indice = listaCitas.origen;
    while (indice != nullptr) {
        if (indice->siguiente == listaCitas.fin) {
            break;
        }
        indice = indice->siguiente;
    }

    CITAS* dato = listaCitas.fin->dato;
    delete listaCitas.fin;
    listaCitas.fin = indice;
    if (indice != nullptr)
        indice->siguiente = nullptr;
    return dato;
}

CITAS* eliminarCitaEnMedio(WCHAR* buscar) {
    NODO_CITA* busqueda = buscarCitaPorCliente(buscar);
    if (busqueda == nullptr)
        return nullptr;

    if (busqueda == listaCitas.origen)
        return eliminarCitaInicio();
    else if (busqueda == listaCitas.fin)
        return eliminarCitaFinal();

    NODO_CITA* indice = listaCitas.origen;
    while (indice != nullptr) {
        if (indice->siguiente == busqueda)
            break;
        indice = indice->siguiente;
    }

    CITAS* dato = busqueda->dato;
    if (indice != nullptr)
        indice->siguiente = busqueda->siguiente;

    delete busqueda;
    return dato;
}
void CerrarPrograma(HWND hWnd) {
    NODO_DOCTOR* dato = listaDoctores.origen;
    fstream loggeado;
    loggeado.open("DATOS.bin", ios::out | ios::binary | ios::trunc);

    if (hWnd != NULL) {
        NODO_DOCTOR* dato = listaDoctores.origen;
        if(loggeado.is_open())
        {
            while (dato != NULL) {
                loggeado.write((char*)dato, sizeof(doctores));
                dato = dato->siguiente;
            }
        }
        loggeado.close();
    }
}
DOCTOR* obtenerDoctorSesion(const wstring& us) {
    auto it = doctores.find(us); // Buscar al doctor por su nombre de usuario 

    if (it != doctores.end()) {
        return &(it->second); // Devolver el doctor encontrado 
    }

    return nullptr; // No se encontró al doctor 
}
bool guardarDoctorEnArchivo(const DOCTOR& doctor) {
    std::ofstream archivo("doctores.bin", std::ios::binary | std::ios::app);

    if (!archivo.is_open()) {
        return false; // No se pudo abrir el archivo
    }

    archivo.write(reinterpret_cast<const char*>(&doctor), sizeof(DOCTOR));
    archivo.close();
    return true;
}

// Función para guardar una estructura CITAS en un archivo binario
bool guardarCitaEnArchivo(const CITAS& cita) {
    std::ofstream archivo("citas.bin", std::ios::binary | std::ios::app);

    if (!archivo.is_open()) {
        return false; // No se pudo abrir el archivo
    }

    archivo.write(reinterpret_cast<const char*>(&cita), sizeof(CITAS));
    archivo.close();
    return true;
}
void agregarespecieFinal(especie* dato) {
    NODO_especie* nuevoNodoespecie = new NODO_especie();
    nuevoNodoespecie->dato = dato;
    nuevoNodoespecie->siguiente = nullptr;

    if (lista_especies.origen == nullptr) {
        lista_especies.origen = nuevoNodoespecie;
        lista_especies.fin = nuevoNodoespecie;
        nuevoNodoespecie->ante = nullptr;
    }
    else {
        nuevoNodoespecie->ante = lista_especies.fin;
        lista_especies.fin->siguiente = nuevoNodoespecie;
        lista_especies.fin = nuevoNodoespecie; 
    }
}
especie* crearespecie(WCHAR* ESP) {
    especie* nuevoespecie = new especie();
    wcscpy_s(nuevoespecie->ESP, 100, ESP);
    return nuevoespecie;
}
//void SEGURO(HWND hwnd) {
//    NODO_doctor*dato = Lista
//}