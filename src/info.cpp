#include "info.h"
#include "setup.h"

#if defined(DEMO_VERSION)
QString p_name("bkstat lite");
QString p_resource_prefix("bkstatlite");
#else
#if defined(DEBUG_VERSION)
QString p_name("bkstat dev");
QString p_resource_prefix("bkstatfull");
#else
QString p_name("bkstat full");
QString p_resource_prefix("bkstatfull");
#endif
#endif
QString p_translation_file("bkstat");
#if defined(Q_OS_ANDROID)
QString p_vers("0.0.0");
QString p_build("20130614");
#else
QString p_vers("1.4.1");
QString p_build("20130416");
#endif
QString p_contact("caminac@gmail.com");
QString p_website("caminac.altervista.org");

#if defined(Q_OS_SYMBIAN)
QString p_platform("Symbian");
#elif defined(Q_WS_WIN)
QString p_platform("Windows");
#else
QString p_platform("unknown");
#endif
