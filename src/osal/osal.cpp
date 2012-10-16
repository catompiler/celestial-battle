#include "osal.h" 

namespace osal{
    
namespace fs{
 
const std::string separator()
{
    return std::string(
#ifdef OS_WINDOWS
                "\\"
#else
                "/"
#endif
        );
}
    
}//fs

}//osal

