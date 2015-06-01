//
//  MyMacroses.h
//  Game3
//
//  Created by Stepanov Ilia on 18/05/15.
//
//

#ifndef Game3_MyMacroses_h
#define Game3_MyMacroses_h

#define CREATE_FUNC_WITH_ONE_PARAM(__TYPE__, __PARAM_TYPE__, __PARAM_VAL__) \
static __TYPE__* createWithParam(__PARAM_TYPE__, __PARAM_VAL__) \
{ \
__TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
if (pRet && pRet->initWithParam(__PARAM_VAL__)) \
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
