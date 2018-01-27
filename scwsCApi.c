#include <stdio.h>
#include <scws/scws.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <string.h>
#include <stdlib.h>
#define SCWS_PREFIX     "/usr/local/scws"

static int run(lua_State *L)
{
  scws_t s;
  scws_top_t res,cur;
  const char *text1 = lua_tostring(L, -2);
  const char *xpath = lua_tostring(L, -1);	
  //char *text1 = text;
  char * ret[11];
  int i = 0;
  if (!(s = scws_new())) {
    printf("ERROR: cann't init the scws!\n");
    exit(-1);
  }
  scws_set_charset(s, "utf8");
  scws_set_dict(s, xpath, SCWS_XDICT_XDB);
  //scws_set_rule(s, "/usr/local/scws/etc/rules.utf8.ini");
  //printf(text1);
  scws_send_text(s, text1, strlen(text1));
  //res = scws_get_tops(s,10,"@,en");
  lua_newtable(L);                    //新建一个表，并压入栈顶
  //lua_pushnumber(L,-1);            
  //lua_rawseti(L,-2,0);
  res = cur = scws_get_tops(s,10,"@,en");
    while (cur != NULL)
    {
      lua_pushstring(L,cur->word);        //将数组的数据入栈
      lua_rawseti(L,-2,i+1);                //将刚刚入栈的数据设置为数组的第n+1个数据，同时这个数据会自动从栈里pop
      //ret[i] = cur->word;
      cur = cur->next;
      i++;
    }
  scws_free_tops(res);
  scws_free(s);
  return 1;
}
static const struct luaL_Reg mylibstest[] = { 
     {"run",run},
     {NULL,NULL} 
}; 
int luaopen_scwsserver(lua_State *L){
        //lua_State* L = luaL_newstate(); 
        //luaL_openlibs(L);
	//const char * libName = "scwss";
       luaL_register(L,"scwsserver",mylibstest);   
       //luaL_newlib(L, mylibs);
    return 1;
}
//gcc -fPIC -shared -o scwsserver.so -I/usr/local/scws/include -I/usr/local/openresty/luajit/include/luajit-2.1 -L/usr/local/scws/lib -L/usr/local/openresty/luajit/lib scwsCApi2.c -lscws -lluajit-5.1
