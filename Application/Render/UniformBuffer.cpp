#include "UniformBuffer.h"

namespace Nome
{

CUniformMemberDecl::CUniformMemberDecl(std::string keyword, std::string name)
    : HLSLKeyword(keyword), Name(name)
{
}

}
