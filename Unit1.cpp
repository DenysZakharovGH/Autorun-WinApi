//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------

int QueryKey(HKEY hKey)
{
        TCHAR    achKey[MAX_PATH];   // buffer for subkey name
        DWORD    cbName;                   // size of name string
        TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name
        DWORD    cchClassName = MAX_PATH;  // size of class string
        DWORD    cSubKeys=0;               // number of subkeys
        DWORD    cbMaxSubKey;              // longest subkey size
        DWORD    cchMaxClass;              // longest class string
        DWORD    cValues;              // number of values for key
        DWORD    cchMaxValue;          // longest value name
        DWORD    cbMaxValueData;       // longest value data
        DWORD    cbSecurityDescriptor; // size of security descriptor
        FILETIME ftLastWriteTime;      // last write time

        DWORD i, retCode;

        TCHAR  achValue[MAX_PATH];
        DWORD cchValue = MAX_PATH;

// Get the class name and the value count.
        retCode = RegQueryInfoKey(
                hKey,                    // key handle
                achClass,                // buffer for class name
                &cchClassName,           // size of class string
                NULL,                    // reserved
                &cSubKeys,               // number of subkeys
                &cbMaxSubKey,            // longest subkey size
                &cchMaxClass,            // longest class string
                &cValues,                // number of values for this key
                &cchMaxValue,            // longest value name
                &cbMaxValueData,         // longest value data
                &cbSecurityDescriptor,   // security descriptor
                &ftLastWriteTime);       // last write time


// Enumerate the key values.
//cValues - numbers of autorun values

        if (cValues)
        {

                TCHAR lpDataBuffer[100];
                for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++)
                {
                        cchValue = MAX_PATH;
                        retCode = RegEnumValue(hKey, i,
                                achValue,
                                &cchValue,
                                NULL,
                                NULL,
                                lpDataBuffer,
                                &cchValue);

                if (retCode == ERROR_SUCCESS )
                {
                        Form1->ListBox2->Items->Add(lpDataBuffer);
                        Form1->ListBox1->Items->Add(achValue);
                }

                }//for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++)
        }//if (cValues)
        return cValues;
}
//---------------------------------------------------------------------------
HKEY GetRegisterKey(HKEY HkeyUserChoice,LPCSTR UserChoice){
        HKEY hTestKey=NULL;

        if(RegOpenKeyEx(HkeyUserChoice,
        UserChoice,
        0, KEY_ALL_ACCESS,
        &hTestKey) == ERROR_SUCCESS)
        {
                return hTestKey;
        }
}
void ShowQueryKey(){
        Form1 -> ListBox1->Clear();
        Form1 -> ListBox2->Clear();

        QueryKey(GetRegisterKey(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Run"));
        QueryKey(GetRegisterKey(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce"));
        QueryKey(GetRegisterKey(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Run"));
        QueryKey(GetRegisterKey(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce"));
}
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{

        ShowQueryKey();
}





void __fastcall TForm1::Button1Click(TObject *Sender)
{
        Form2->Show();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::ListBox1Click(TObject *Sender)
{
        Label5->Caption=ListBox1->Items->Strings[ListBox1->ItemIndex];

        Label4->Caption=ListBox2->Items->Strings[ListBox1->ItemIndex];

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
        if(RegDeleteValue(GetRegisterKey(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Run"),Label5->Caption.c_str()) != ERROR_SUCCESS)
                if(RegDeleteValue(GetRegisterKey(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce"),Label5->Caption.c_str()) != ERROR_SUCCESS)
                        if(RegDeleteValue(GetRegisterKey(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\Run"),Label5->Caption.c_str()) != ERROR_SUCCESS)
                                RegDeleteValue(GetRegisterKey(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce"),Label5->Caption.c_str());

        ShowQueryKey();
        Label5->Caption="";
         Label4->Caption="";
}
//---------------------------------------------------------------------------



void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
         ShowQueryKey();
       Label5->Caption="";
       Label4->Caption="";
}
//---------------------------------------------------------------------------


void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
        Form3->Show();        
}
//---------------------------------------------------------------------------







