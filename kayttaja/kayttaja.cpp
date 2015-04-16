// kayttaja.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
// Kirjasto toisesta projektista
#include "dllLaskin.h"
#include "windows.h";

int _tmain(int argc, _TCHAR* argv[])
{

	double a = 3.5;
	double b = 4.3;
	char c[200] ="";
	char buf[255] = {0};
    DWORD dwType = 0;
    DWORD dwBufSize = sizeof(buf);
	HKEY hKey;
    DWORD dwDisposition;
	// Tarkistaa kielen 
	#ifdef __cplusplus
		cout << "a:n arvo = " << a << " b:n arvo = " << b << endl << endl;
		// tarkistaa merkkijonon arvon ja pituuden ( varattu 200 merkkiä)
		while(!(stricmp ("-e", c) == 0) || (sizeof(c)/sizeof(*c)) > 200)
		{
			cout << "Anna komentoriviparametri ( -h tulostaa komentorivioptiot ): ";
			cin >> c;
			if (stricmp ("-h", c) == 0)
			{
				cout << "Komentoriviparametrit: " << endl;
				cout << "-s summa " << endl << "-v vahennyslasku " << endl << "-j jakolasku " << endl << "-k kertolasku " << endl << "-e lopeta ohjelma " << endl << endl;					
			}
			else if(stricmp ("-k", c) == 0)
			{
				double result = multiply(a, b);
				cout << "Kertolasku: " << result << endl << endl;
				// Tallentaa laskun tuloksen rekisteriin 
				    if(RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\uusilaskin\\"), 0, NULL, 0, KEY_WRITE, NULL, &hKey, &dwDisposition) == ERROR_SUCCESS) 
					{
						long setRes = RegSetValueEx(hKey, TEXT("kertolaskun arvo"), 0, REG_BINARY, (LPBYTE)&result, sizeof(double));
						 if (setRes == ERROR_SUCCESS) {
								cout << "Rekisteriin kirjoitus onnistui\n";
							} else {
								cout << "Rekisteriin kirjoitus epaonnistui\n";
							}
						 // Sulkee avaimen
						RegCloseKey(hKey);
					}
					else
						printf("Virhe");
				}
			else if(stricmp ("-s", c) == 0)
			{
				double sumres = sum(a,b);
				cout  << "Summa: "<< sumres << endl << endl;
					if(RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\uusilaskin\\"), 0, NULL, 0, KEY_WRITE, NULL, &hKey, &dwDisposition) == ERROR_SUCCESS) 
					{
						long setRes = RegSetValueEx(hKey, TEXT("summa"), 0, REG_BINARY, (LPBYTE)&sumres, sizeof(double));
						 if (setRes == ERROR_SUCCESS) {
								cout << "Rekisteriin kirjoitus onnistui\n";
							} else {
								cout << "Rekisteriin kirjoitus epaonnistui\n";
							}
						RegCloseKey(hKey);
					}
					else
						printf("Virhe");
			}
			else if(stricmp ("-j", c) == 0)
			{
				double divres = divide(a,b);
					cout << "Jakolasku: " << divres << endl << endl;
					if(RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\uusilaskin\\"), 0, NULL, 0, KEY_WRITE, NULL, &hKey, &dwDisposition) == ERROR_SUCCESS) 
					{
						long setRes = RegSetValueEx(hKey, TEXT("jakolaskun arvo"), 0, REG_BINARY, (LPBYTE)&divres, sizeof(double));
						 if (setRes == ERROR_SUCCESS) {
								cout << "Rekisteriin kirjoitus onnistui\n";
							} else {
								cout << "Rekisteriin kirjoitus epaonnistui\n";
							}
						RegCloseKey(hKey);
					}
					else
						printf("Virhe");
			}
			else if(stricmp ("-v", c) == 0)
			{
				double subres = subtr(a,b);
				cout << "Vahennuslasku: " << subtr(a,b) << endl << endl;
				if(RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("SOFTWARE\\uusilaskin\\"), 0, NULL, 0, KEY_WRITE, NULL, &hKey, &dwDisposition) == ERROR_SUCCESS) 
				{
					long setRes = RegSetValueEx(hKey, TEXT("vahennuslaskun arvo"), 0, REG_BINARY, (LPBYTE)&subres, sizeof(double));
						if (setRes == ERROR_SUCCESS) {
							cout << "Rekisteriin kirjoitus onnistui\n";
						} else {
							cout << "Rekisteriin kirjoitus epaonnistui\n";
						}
					RegCloseKey(hKey);
				}
				else
					printf("Virhe");
			}
			else 
			{
				cout << "Virhe" << endl << endl;
			}
		}
		// Tulostaa kaikki rekisteristä löytyvät arvot vuorotellen
		if( RegOpenKey(HKEY_CURRENT_USER, TEXT("SOFTWARE\\uusilaskin\\"), &hKey) == ERROR_SUCCESS)
		{
			dwType = REG_SZ;
			if( RegQueryValueEx(hKey,TEXT("summa"),0, &dwType, (BYTE*)buf, &dwBufSize) == ERROR_SUCCESS)
			{
				cout << "summa on '" << buf << "'\n";
			}
			else
				cout << "virhe\n";
			RegCloseKey(hKey);
		}
		else
			cout << "virhe\n";
		if( RegOpenKey(HKEY_CURRENT_USER, TEXT("SOFTWARE\\uusilaskin\\"), &hKey) == ERROR_SUCCESS)
			{
				dwType = REG_SZ;
				if( RegQueryValueEx(hKey,TEXT("jakolaskun arvo"),0, &dwType, (BYTE*)buf, &dwBufSize) == ERROR_SUCCESS)
				{
					cout << "jakolaskun arvo on '" << buf << "'\n";
				}
				else
					cout << "virhe\n";
				RegCloseKey(hKey);
			}
			else
				cout << "virhe\n";
		if( RegOpenKey(HKEY_CURRENT_USER, TEXT("SOFTWARE\\uusilaskin\\"), &hKey) == ERROR_SUCCESS)
			{
				dwType = REG_SZ;
				if( RegQueryValueEx(hKey,TEXT("kertolaskun arvo"),0, &dwType, (BYTE*)buf, &dwBufSize) == ERROR_SUCCESS)
				{
					cout << "kertolaskun arvo on '" << buf << "'\n";
				}
				else
					cout << "virhe\n";
				RegCloseKey(hKey);
			}
			else
				cout << "virhe\n";
			if( RegOpenKey(HKEY_CURRENT_USER, TEXT("SOFTWARE\\uusilaskin\\"), &hKey) == ERROR_SUCCESS)
			{
				dwType = REG_SZ;
				if( RegQueryValueEx(hKey,TEXT("vahennuslaskun arvo"),0, &dwType, (BYTE*)buf, &dwBufSize) == ERROR_SUCCESS)
				{
					cout << "vahennuslaskun arvo on '" << buf << "'\n";
				}
				else
					cout << "virhe\n";
				RegCloseKey(hKey);
			}
			else
				 cout << "virhe\n";
		return 0;

	#else
		printf("a:n arvo = %g, b:n arvo = %g\n", a, b);
		while(!(stricmp ("-e", c) == 0) || (sizeof(c)/sizeof(*c)) > 200)
		{
			printf( "Anna komentoriviparametri ( -h tulostaa komentorivioptiot ): ");
			scanf("%c", &c);
			if (stricmp ("-h", c) == 0)
			{
				printf("Komentoriviparametrit: n");
				printf("-s summa \n-v vahennyslasku  \n-j jakolasku \n-k kertolasku  \n- e lopeta ohjelma  \n");					
			}
			else if(stricmp ("-k", c) == 0)
			{
				printf("%g + %g = %g\n", a, b, multiply(a, b));
			}
			else if(stricmp ("-s", c) == 0)
			{
				printf("%g + %g = %g\n", a, b, sum(a, b));
			}
			else if(stricmp ("-j", c) == 0)
			{
				printf("%g + %g = %g\n", a, b, divide(a, b));
			}
			else if(stricmp ("-v", c) == 0)
			{
				printf("%g + %g = %g\n", a, b, subtr(a, b));
			}
			else 
			{
				printf("Virhe");
			}
		}
		return 0;
	#endif
}

