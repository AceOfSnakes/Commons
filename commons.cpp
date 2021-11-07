#include "commons.h"
#include <QOperatingSystemVersion>
#include <QSettings>
#if defined(Q_OS_WIN)
#include <qt_windows.h>
#endif

Commons::Commons() {

}

QString Commons::prettyProductName() {
#if defined(Q_OS_WIN)
    QSettings m("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
    QSettings::Registry64Format);

    QString displayVersion = m.value("DisplayVersion").toString();

    OSVERSIONINFOEX osver;
    //::GetVersionEx(osver);
    osver.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    if(!GetVersionEx((OSVERSIONINFO*)&osver)) {
        return QSysInfo::prettyProductName();
    }
    const bool workstation = osver.wProductType == VER_NT_WORKSTATION;
    QOperatingSystemVersion version = QOperatingSystemVersion::current();

#define Q_WINVER(major, minor) (major << 8 | minor)
    switch (Q_WINVER(version.majorVersion(), version.minorVersion())) {
        case Q_WINVER(10, 0):
            if (!displayVersion.isEmpty()) {
                if(((workstation && version.microVersion() >= 21327) || (!workstation && version.microVersion() >= 17623)))
                    return QString(workstation ? "Windows 11" : "Windows Server 2022").append(" Version ").append(displayVersion);
                else
                    return QString(workstation ? "Windows 10" : "Windows Server 2016").append(" Version ").append(displayVersion);
            }
    }
#undef Q_WINVER

#endif
    return QSysInfo::prettyProductName();
}

QString Commons::compilerQString() {
    QString compiler;
#ifdef __clang_version__
    compiler.append(QString().asprintf("Compiler: clang %s",  __clang_version__));
#elif defined __GNUC__ && defined __VERSION__
    compiler.append(QString().asprintf("Compiler: gcc %s", __VERSION__));
#elif defined _MSC_VER
    compiler.append("Compiler: Visual Studio");
#if 0    
    /*
     * https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros
     */
#elif _MSC_VER >= 1930
    compiler.append(" 2022 / MSVC++ 17.0");
#elif _MSC_VER >= 1929
#if _MSC_FULL_VER >= 192930100
    compiler.append(" 2019 / MSVC++ 16.11");
#else
    compiler.append(" 2019 / MSVC++ 16.10");
#endif
#elif _MSC_VER >= 1928
#if _MSC_FULL_VER >= 192829500
    compiler.append(" 2019 / MSVC++ 16.9");
#else
    compiler.append(" 2019 / MSVC++ 16.8");
#endif
#elif _MSC_VER >= 1920
    compiler.append(" 2019 / MSVC++ 16.").append(QString().asprintf("%d",((_MSC_VER % 100) - 20)));
#elif _MSC_VER > 1911
    compiler.append(" 2017 / MSVC++ 15.").append(QString().asprintf("%d",((_MSC_VER % 100) - 7)));
#elif _MSC_VER == 1911
    compiler.append(" 2017 / MSVC++ 15.3");
#elif _MSC_VER == 1910
    compiler.append(" 2017 / MSVC++ 15.0");
#elif _MSC_VER == 1900
    compiler.append(" 2015 / MSVC++ 14.0");
#elif _MSC_VER == 1800
    compiler.append(" 2013 / MSVC++ 12.0");
#elif _MSC_VER == 1700
    compiler.append(" 2012 / MSVC++ 11.0");
#elif _MSC_VER == 1600
    compiler.append(" 2010 / MSVC++ 10.0");
#elif  _MSC_VER == 1500
    compiler.append(" 2008 / MSVC++ 9.0");
#elif  _MSC_VER == 1400
    compiler.append(" 2005 / MSVC++ 8.0");
#elif  _MSC_VER == 1310
    compiler.append(" .NET 2003 / MSVC++ 7.1");
#elif  _MSC_VER == 1300
    compiler.append(" .NET 2002 / MSVC++ 7.0");
#elif  _MSC_VER == 1300
    compiler.append(" .NET 2002 / MSVC++ 7.0");
#else
    compiler.append(", unrecognised version");
#endif
    compiler.append(QString().asprintf(" (_MSC_VER=%d, _MSC_FULL_VER=%d)", (int)_MSC_VER,(int)_MSC_FULL_VER));
#endif
    return compiler;
}
