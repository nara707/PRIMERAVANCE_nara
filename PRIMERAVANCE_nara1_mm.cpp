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
#include <memory>

#define MAX_LOADSTRING 100
class CITAS;
class DOCTOR;

constexpr auto IDC_T = 1000;

using namespace std;

HWND hWnd = nullptr;


class DOCTOR{
public:
    
    WCHAR nom[100];
    WCHAR contra[100];
    WCHAR ced[100];
    WCHAR us[15];
    vector<shared_ptr<CITAS>> citas;
    shared_ptr<DOCTOR> next;
    shared_ptr<DOCTOR> previous;
};

class CITAS {
public:
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
    WCHAR estado[100];
    WCHAR especie[100];

    
    shared_ptr<DOCTOR> loggeado;  
    shared_ptr<CITAS> next; 
    shared_ptr<CITAS> ante; 
    
};
//struct Cerrar {
//    DOCTOR doctor;
//    CITAS citas;
//};

class especie {
public:
   
    WCHAR ESP[100];
    shared_ptr<DOCTOR> Asociado; 
    shared_ptr<especie> next;
    shared_ptr<especie> ante;
}/*lista_especie*/; 

struct NODO_DOCTOR {
    DOCTOR* dato;
    NODO_DOCTOR* next;
    NODO_DOCTOR* ante;
};

struct LISTA_DOCTORES {
    NODO_DOCTOR* origen;
    NODO_DOCTOR* fin;
};

struct NODO_especie {
    especie* dato;
    NODO_especie* next;
    NODO_especie* ante;
};

struct NODO_CITA {
    CITAS* dato;
    NODO_CITA* next;
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
NODO_DOCTOR* loggeado = nullptr;
LISTA_CITAS listaCitas;
NODO_especie* logesp = nullptr;
NODO_CITA* Asociado = nullptr;
NODO_CITA* ses = nullptr; 


map<wstring, DOCTOR> doctores;
map<wstring, DOCTOR> agendaDoctores;
map<wstring, especie> Especies;
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
void ordenarCitasPorMes();
void eliminarListaDoctores(LISTA_DOCTORES* listaDoctores);
DOCTOR* crearDoctor(WCHAR* us, WCHAR* contra, WCHAR* nom, WCHAR* ced);
especie* crearespecie(WCHAR* ESP);
CITAS* crearCita(WCHAR* cliente, WCHAR* masc, WCHAR* motivo, WCHAR* tel, WCHAR* precio, WCHAR* year, WCHAR* month, WCHAR* day, WCHAR* hora, WCHAR* mn, WCHAR* seg, WCHAR* estado,WCHAR* especie);
NODO_DOCTOR* nuevoNodo(DOCTOR* dato);
NODO_CITA* nuevoNodo(CITAS* dato);
NODO_especie* nuevoNodo(especie* dato);
NODO_DOCTOR* buscarUsuario(LISTA_DOCTORES* listaDoctores, WCHAR* buscar);
NODO_CITA* buscarCita(LISTA_CITAS* listaCitas, WCHAR* buscar);
NODO_especie* buscarespecie(lista_especie* lista_especies, WCHAR* buscar);
NODO_DOCTOR* buscarDoctorPorUsuario(WCHAR* buscar);
NODO_CITA* buscarCitaPorCliente(WCHAR* buscar);
CITAS* eliminarCITA(WCHAR* cliente);
NODO_especie* buscarEpeciePorEspecie(WCHAR* buscar);
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
CITAS* eliminarCitaInicio();
CITAS* eliminarCitaFinal();
CITAS* eliminarCitaEnMedio(WCHAR* buscar);

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
        ordenarCitasPorMes(); 
        Asociado = listaCitas.origen;
            while(Asociado!=NULL)
            {
                SendMessage(GetDlgItem(hWnd, IDC_LIST1),LB_ADDSTRING, 0, (LPARAM)Asociado->dato->month);
                Asociado = Asociado->next; 
            }
    } break;

    case WM_COMMAND: 
    {

        int id = LOWORD(wParam);
        int wmEvent = HIWORD(wParam);
        if (menu(id, hWnd)) 
        
            return FALSE;
        
        if (LOWORD(wParam) == IDC_MOD) { 

            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(MODIFICAR), NULL, MODIFICARCallback);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0); 

        }
        if (LOWORD(wParam) == AGENDAR) { 

            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(CITA), NULL, VENTANACITACallback);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);

        }

        /*switch (id) 
        {*/
        if (LOWORD(wParam) == IDC_LIST1) {

            switch (HIWORD(wParam)) {

            case LBN_DBLCLK: {

                char texto[50] = {};
                int seleccion = 0;

                seleccion = SendDlgItemMessage(hWnd, IDC_LIST1, LB_GETCURSEL, 0, 0);
                SendDlgItemMessage(hWnd, IDC_LIST1, LB_GETTEXT, seleccion, (LPARAM)texto);

               /* int len = WideCharToMultiByte(CP_ACP, 0, texto, -1, NULL, 0, NULL, NULL);
                wchar_t* texto_wide = new wchar_t[len];
                MultiByteToWideChar(CP_ACP, 0, texto, -1, texto_wide, len);*/

                NODO_CITA* ses = listaCitas.origen;

                while (ses != nullptr) 
                {
                   
                


                if (ses->dato != nullptr && ses->dato->cliente != nullptr && strcmp(texto, (char*)ses->dato->cliente) == 0)
                {

                    SetDlgItemText(hWnd, IDC_1, ses->dato->cliente);
                    SetDlgItemText(hWnd, IDC_3, ses->dato->tel);
                    SetDlgItemText(hWnd, IDC_2, ses->dato->masc);
                    SetDlgItemText(hWnd, IDC_5, ses->dato->motivo);
                    SetDlgItemText(hWnd, IDC_6, ses->dato->precio);
                    SetDlgItemText(hWnd, IDC_EDIT7, ses->dato->estado); 
                    SetDlgItemText(hWnd, IDC_FA, ses->dato->day);
                    SetDlgItemText(hWnd, IDC_HA, ses->dato->hora);
                    SetDlgItemText(hWnd, IDC_EDIT4, ses->dato->especie); 
                    break;
                }
                ses = ses->next; 
                }
                /*delete[] texto_wide;*/
            }break;

            }


        }
        if (LOWORD(wParam) == IDCBORRRAR) { 

            WCHAR* cliente = ses->dato->cliente;
            eliminarCITA(cliente);
            SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_RESETCONTENT, 0, 0);

            Asociado = listaCitas.origen; 

            while (Asociado != nullptr) {

                SendMessage(GetDlgItem(hWnd, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)Asociado->dato->cliente); 
                Asociado = Asociado->next;  

            }

            SetDlgItemText(hWnd, IDC_1, (WCHAR*)" ");
            SetDlgItemText(hWnd, IDC_2, (WCHAR*)" ");
            SetDlgItemText(hWnd, IDC_3, (WCHAR*)" ");
            SetDlgItemText(hWnd, IDC_4, (WCHAR*)" ");
            SetDlgItemText(hWnd, IDC_5, (WCHAR*)" ");
            SetDlgItemText(hWnd, IDC_6, (WCHAR*)" ");
            SetDlgItemText(hWnd, IDC_7, (WCHAR*)" ");
            SetDlgItemText(hWnd, IDC_HA, (WCHAR*)" ");
            SetDlgItemText(hWnd, IDC_FA, (WCHAR*)" "); 



        }
       

        //default:
        //    return DefWindowProc(hWnd, message, wParam, lParam); 
    }break;
    case WM_CLOSE: {

        int res = MessageBox(hWnd, L"¿Realmente deseas salir?", L"ALERTA", MB_OKCANCEL | MB_ICONWARNING);

        if (res == IDOK)
        {
            CerrarPrograma(hWnd);
            EndDialog(hWnd, 0);
        }

    }break;

    case WM_DESTROY: 
        PostQuitMessage(0);
        break;
    /*case default:
    {
        return FALSE;
    }break;*/
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
        /*NODO_especie* nodoActual = lista_especies.origen;*/

        if (g_hSelectedImage != nullptr)
        {
            SendMessage(GetDlgItem(hWnd, FOTOC), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)g_hSelectedImage); 
        }
        /*HWND hListBox = GetDlgItem(hWnd, IDC_ESPECIE);*/

        /*NODO_especie* nodo_especie = buscarEpeciePorEspecie(ESP);*/
        logesp = lista_especies.origen; 
        while(logesp != NULL) { 
            SendMessage(GetDlgItem(hWnd,IDC_ESPECIE), LB_ADDSTRING, 0, (LPARAM)logesp->dato->ESP); 
            logesp = logesp->next;  

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
            GetDlgItemText(hWnd, IDC_TEL, tel, 100);

            WCHAR precio[100] = { 0 };
            GetDlgItemText(hWnd, IDC_COST, precio, 100);

            WCHAR day[100] = { 0 };
            GetDlgItemText(hWnd, IDC_F, day, 100);

            WCHAR month[100] = { 0 };
            GetDlgItemText(hWnd, IDC_F, month, 100);

            WCHAR year[100] = { 0 };
            GetDlgItemText(hWnd, IDC_F, year, 100);

            WCHAR hora[100] = { 0 };
            GetDlgItemText(hWnd, IDC_H, hora, 100);

            WCHAR seg[100] = { 0 };
            GetDlgItemText(hWnd, IDC_H, seg, 100);

            WCHAR estado[100] = { 0 };
            GetDlgItemText(hWnd, IDC_7, estado, 100);

            WCHAR especie[100] = { 0 };
            GetDlgItemText(hWnd, IDC_4, especie, 100);

            
            WCHAR mn[100] = { 0 };
            GetDlgItemText(hWnd, IDC_H, mn, 100);

            int dia = std::wcstol(day, nullptr, 10);
            int mes = std::wcstol(month, nullptr, 10);
            int anio = std::wcstol(year, nullptr, 10);
            int horas = std::wcstol(hora, nullptr, 10);
            int minutos = std::wcstol(mn, nullptr, 10);
            int segundos = std::wcstol(seg, nullptr, 10);

            agregarCitaFinal(crearCita(cliente, mascota, motivo, tel, precio, year, month, day, hora, mn, seg, estado, especie));
            MessageBox(hWnd, L"CITA", L"CITA GUARDADA >.O", MB_OK|MB_ICONINFORMATION);

            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(AGENDA), NULL, AGENDACallback);
            ShowWindow(ventana, SW_SHOW);
            CerrarPrograma(hWnd); 
            EndDialog(hWnd, 0); 

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
        /*case default:
            {
            return FALSE;
            }*/
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
    /*case default:
        {
        return FALSE;
        }*/
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
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(CITA), NULL, VENTANACITACallback);
            ShowWindow(ventana, SW_SHOW);
            CerrarPrograma(hWnd);
            EndDialog(hWnd, 0); 
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
       
    } break;
    case IDM_EXIT: {

        int res = MessageBox(hWnd, L"¿Realmente deseas salir?", L"ALERTA", MB_OKCANCEL | MB_ICONWARNING);

        if (res == IDOK)
        {
            CerrarPrograma(hWnd);

        }

    }break;
    default: {return false; }break;
    }
    return true; 
} 

void eliminarListaCitas(LISTA_CITAS* listaCitas) {
    NODO_CITA* actual = listaCitas->origen;
    NODO_CITA* Asociado = nullptr;

    while (actual != nullptr) {
        Asociado = actual->next; 
        delete actual->dato; // Liberar memoria del dato CITA
        delete actual;       // Liberar memoria del nodo NODO_CITA
        actual = Asociado;
    }

    // Reiniciar la lista, estableciendo origen y fin como nullptr
    listaCitas->origen = nullptr;
    listaCitas->fin = nullptr;
}
void eliminarListaDoctores(LISTA_DOCTORES* listaDoctores) {
    NODO_DOCTOR* actual = listaDoctores->origen;
    NODO_DOCTOR* loggeado = nullptr;

    while (actual != nullptr) {
        loggeado = actual->next;
        delete actual->dato; // Liberar memoria del dato DOCTOR
        delete actual;       // Liberar memoria del nodo NODO_DOCTOR
        actual = loggeado;
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
CITAS* crearCita(WCHAR* cliente, WCHAR* masc, WCHAR* motivo, WCHAR* tel, WCHAR* precio, WCHAR* year, WCHAR* month, WCHAR* day, WCHAR* hora, WCHAR* mn, WCHAR* seg, WCHAR* especie, WCHAR* estado) {
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
    wcscpy_s(nuevoCita->estado, 100, seg);
    wcscpy_s(nuevoCita->especie, 100, seg);


    

    return nuevoCita;
}
NODO_DOCTOR* nuevoNodo(DOCTOR* dato) {
    NODO_DOCTOR* nuevoNodoDoctor = new NODO_DOCTOR();
    nuevoNodoDoctor->dato = dato;
    nuevoNodoDoctor->next = nullptr; 
    nuevoNodoDoctor->ante = nullptr;

    return nuevoNodoDoctor;
}
NODO_especie* nuevoNodo(especie* dato) {
    NODO_especie* nuevoNodoespecie = new NODO_especie();
    nuevoNodoespecie->dato = dato;
    nuevoNodoespecie->next = nullptr;
    nuevoNodoespecie->ante = nullptr; 
    return nuevoNodoespecie;
}
NODO_CITA* nuevoNodo(CITAS* dato) {
    NODO_CITA* nuevoNodoCita = new NODO_CITA();
    nuevoNodoCita->dato = dato;
    nuevoNodoCita->next = nullptr;
    nuevoNodoCita->ante = nullptr;

    return nuevoNodoCita;
}
NODO_especie* buscarespecie(lista_especie* lista_especies, WCHAR* buscar) {
    NODO_especie* actual = lista_especies->origen;
    while(actual != nullptr) {
        if (wcscmp(actual->dato->ESP, buscar) == 0) { 
            return actual;
        }
        actual = actual->next; 
    }
    return nullptr; // No se encont)
}
NODO_DOCTOR* buscarUsuario(LISTA_DOCTORES* listaDoctores, WCHAR* buscar) { 
    NODO_DOCTOR* actual = listaDoctores->origen;

    while (actual != nullptr) {
        if (wcscmp(actual->dato->us, buscar) == 0) {
            return actual;
        }
        actual = actual->next; 
    }
    return nullptr; // No se encontró el usuario
}
NODO_CITA* buscarCita(LISTA_CITAS* listaCitas, WCHAR* buscar) {
    NODO_CITA* actual = listaCitas->origen;

    while (actual != nullptr) {
        if (wcscmp(actual->dato->cliente, buscar) == 0) {
            return actual;
        }
        actual = actual->next; 
    }
    return nullptr; // No se encontró la cita 
}


NODO_DOCTOR* buscarDoctorPorUsuario(WCHAR* buscar) {
   /* if (listaDoctores.origen = NULL)
        return NULL;*/
    NODO_DOCTOR* actual = listaDoctores.origen;

    while (actual != nullptr) {
        if (wcscmp(actual->dato->us, buscar) == 0 || wcscmp(actual->dato->us, buscar) == 0) {
            return actual; // Se encontró el doctor, se devuelve el nodo correspondiente
        }
        actual = actual->next; 
    }

    return nullptr; // No se encontró el doctor en la lista
}
NODO_CITA* buscarCitaPorCliente(WCHAR* buscar) {
    if (listaCitas.origen == nullptr) {
        return nullptr; // La lista está vacía
    }

    NODO_CITA* actual = listaCitas.origen;

    while (actual != nullptr) {
        if (actual->dato != nullptr && wcscmp(actual->dato->cliente, buscar) == 0) {
            return actual; // Se encontró el cliente, se devuelve el nodo correspondiente
        }
        actual = actual->next;
    }

    return nullptr; // No se encontró el cliente en la lista
}

NODO_especie* buscarEpeciePorEspecie(WCHAR* buscar) {
    /*if (listaCitas.origen = NULL)
        return NULL;*/
    NODO_especie* actual = lista_especies.origen;

    while (actual != nullptr) {
        if (wcscmp(actual->dato->ESP, buscar) == 0) {
            return actual; 
        }
        actual = actual->next;
    }

    return nullptr;
}
void agregarDoctorInicio(DOCTOR* dato) {
    NODO_DOCTOR* nuevoNodoDoctor = nuevoNodo(dato);

    if (listaDoctores.origen == nullptr) {
        listaDoctores.origen = nuevoNodoDoctor;
        listaDoctores.fin = nuevoNodoDoctor;
        nuevoNodoDoctor->next = nullptr; 
    }
    else {
        nuevoNodoDoctor->next = listaDoctores.origen;
        listaDoctores.origen->ante = nuevoNodoDoctor;
        listaDoctores.origen = nuevoNodoDoctor;
    }
}

void agregarDoctorFinal(DOCTOR* dato) {
    NODO_DOCTOR* nuevoNodoDoctor = new NODO_DOCTOR();
    nuevoNodoDoctor->dato = dato;
    nuevoNodoDoctor->next = nullptr; 

    if (listaDoctores.origen == nullptr) {
        listaDoctores.origen = nuevoNodoDoctor;
        listaDoctores.fin = nuevoNodoDoctor;
        nuevoNodoDoctor->ante = nullptr;
    }
    else {
        nuevoNodoDoctor->ante = listaDoctores.fin;
        listaDoctores.fin->next = nuevoNodoDoctor; 
        listaDoctores.fin = nuevoNodoDoctor;
    }
}

void agregarDoctorEnMedio(WCHAR* buscar, DOCTOR* dato) {
    NODO_DOCTOR* busqueda = buscarDoctorPorUsuario(buscar);

    if (busqueda == nullptr) {
        return; // No se encontró el nodo de búsqueda, no se puede agregar en medio
    }

    NODO_DOCTOR* nuevoNodoDoctor = nuevoNodo(dato);
    nuevoNodoDoctor->next = busqueda->next;
    busqueda->next = nuevoNodoDoctor; 
     
    if (nuevoNodoDoctor->next != nullptr) {
        nuevoNodoDoctor->next->ante = nuevoNodoDoctor; 
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
        nuevoNodoCita->next = nullptr; 
    }
    else {
        nuevoNodoCita->next = listaCitas.origen;
        listaCitas.origen->ante = nuevoNodoCita;
        listaCitas.origen = nuevoNodoCita;
    }
}

void agregarCitaFinal(CITAS* dato) {
    NODO_CITA* nuevoNodoCita = new NODO_CITA();
    nuevoNodoCita->dato = dato;
    nuevoNodoCita->next = nullptr;

    if (listaCitas.origen == nullptr) {
        listaCitas.origen = nuevoNodoCita;
        listaCitas.fin = nuevoNodoCita;
        nuevoNodoCita->ante = nullptr;
    }
    else {
        nuevoNodoCita->ante = listaCitas.fin;
        listaCitas.fin->next = nuevoNodoCita; 
        listaCitas.fin = nuevoNodoCita;
    }
}

void agregarCitaEnMedio(WCHAR* buscar, CITAS* dato) {
    NODO_CITA* busqueda = buscarCitaPorCliente(buscar);

    if (busqueda == nullptr) {
        return; // No se encontró el nodo de búsqueda, no se puede agregar en medio
    }

    NODO_CITA* nuevoNodoCita = nuevoNodo(dato);
    nuevoNodoCita->next = busqueda->next; 
    busqueda->next = nuevoNodoCita; 

    if (nuevoNodoCita->next != nullptr) { 
        nuevoNodoCita->next->ante = nuevoNodoCita; 
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
    listaDoctores.origen = listaDoctores.origen->next; 
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
        if (indice->next == listaDoctores.fin) {
            break;
        }
        indice = indice->next;
    }

    DOCTOR* dato = listaDoctores.fin->dato;
    delete listaDoctores.fin;
    listaDoctores.fin = indice;

    if (indice != nullptr)
        indice->next = nullptr;

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
        if (indice->next == busqueda) 
            break;
        indice = indice->next; 
    }

    DOCTOR* dato = busqueda->dato;
    if (indice != nullptr)
        indice->next = busqueda->next; 

    delete busqueda;
    return dato;
}

CITAS* eliminarCitaInicio() {
    if (listaCitas.origen == nullptr)
        return nullptr;

    if (listaCitas.origen == listaCitas.fin)
        listaCitas.fin = nullptr;

    NODO_CITA* ante = listaCitas.origen; 
    listaCitas.origen = listaCitas.origen->next; 
    CITAS* dato = ante->dato; 
    delete ante; 
    return dato;
}

CITAS* eliminarCitaFinal() {
    if (listaCitas.origen == nullptr)
        return nullptr;

    if (listaCitas.origen == listaCitas.fin)
        return eliminarCitaInicio();

    NODO_CITA* ses = listaCitas.origen;
    while (ses != nullptr) {
        if (ses->next == listaCitas.fin) { 
            break;
        }
        ses = ses->next; 
    }

    CITAS* dato = listaCitas.fin->dato;
    delete listaCitas.fin;
    listaCitas.fin = ses;
    if (ses != nullptr)
        ses->next = nullptr; 
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

    NODO_CITA* ses = listaCitas.origen;
    while (ses != nullptr) {
        if (ses->next == busqueda) 
            break;
        ses = ses->next; 
    }

    CITAS* dato = busqueda->dato;
    if (ses != nullptr)
        ses->next = busqueda->next;

    delete busqueda;
    return dato;
}
CITAS* eliminarCITA(WCHAR* cliente) {
    NODO_CITA* ses = buscarCitaPorCliente(cliente);
    if (ses == nullptr)
        return nullptr;

    if (ses == listaCitas.origen)
        return eliminarCitaInicio();
    else if (ses == listaCitas.fin)
        return eliminarCitaFinal();

    NODO_CITA* anterior = ses->ante;
    NODO_CITA* siguiente = ses->next;
    CITAS* dato = ses->dato;

    if (anterior != nullptr)
        anterior->next = siguiente;
    if (siguiente != nullptr)
        siguiente->ante = anterior;

    delete ses;
    return dato;
}



void CerrarPrograma(HWND hWnd) {
    NODO_DOCTOR* loggeado = listaDoctores.origen;  
    fstream archivo; 
    archivo.open("DATOS.bin", ios::out | ios::binary | ios::trunc);

    if (loggeado != nullptr) { 
        NODO_DOCTOR* loggeado = listaDoctores.origen; 
        if(archivo.is_open())
        {
            while (loggeado != nullptr) { 
                archivo.write((char*)loggeado, sizeof(doctores));
                loggeado = loggeado->next;  
            }
        }
        archivo.close();
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
    nuevoNodoespecie->next = nullptr; 

    if (lista_especies.origen == nullptr) {
        lista_especies.origen = nuevoNodoespecie;
        lista_especies.fin = nuevoNodoespecie;
        nuevoNodoespecie->ante = nullptr;
    }
    else {
        nuevoNodoespecie->ante = lista_especies.fin;
        lista_especies.fin->next = nuevoNodoespecie;
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

void ordenarCitasPorMes() {
    bool swapped;
    NODO_CITA* ptr1;
    NODO_CITA* lptr = NULL;

    if (listaCitas.origen == NULL)
        return;

    do {
        swapped = false;
        ptr1 = listaCitas.origen;

        while (ptr1->next != lptr) {
            if (wcscmp(ptr1->dato->month, ptr1->next->dato->month) > 0) {
                // Intercambiar las cadenas de caracteres de los meses de las citas
                WCHAR temp[100]; // Ajusta el tamaño según tus necesidades
                wcscpy_s(temp, ptr1->dato->month);
                wcscpy_s(ptr1->dato->month, ptr1->next->dato->month);
                wcscpy_s(ptr1->next->dato->month, temp);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}
