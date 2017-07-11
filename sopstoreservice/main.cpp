#include <SyberosServiceCache>
#include "sopstoreservice_workspace.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    return SYBEROS::SyberosServiceCache::qApplication(argc, argv, new sopstoreservice_Workspace());
}
