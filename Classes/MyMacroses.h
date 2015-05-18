//
//  MyMacroses.h
//  Game3
//
//  Created by Stepanov Ilia on 18/05/15.
//
//

#ifndef Game3_MyMacroses_h
#define Game3_MyMacroses_h

#define CREATE_FUNC_WITH_PARAMS(__TYPE__, __PARAMS__) \
static __TYPE__* create() \
{ \
__TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
if (pRet && pRet->init(__PARAMS__)) \
{ \
pRet->autorelease(); \
return pRet; \
} \
else \
{ \
delete pRet; \
pRet = NULL; \
return NULL; \
} \
}


#endif
