luajit_scws
===============
#编译：
```bash
gcc -fPIC -shared -o scwsserver.so -I/usr/local/scws/include -I/usr/local/openresty/luajit/include/luajit-2.1 -L/usr/local/scws/lib -L/usr/local/openresty/luajit/lib scwsCApi2.c -lscws -lluajit-5.1
```
#使用：
  本测试使用 openresty
  拷贝scwsserver.so到openresty lualib下

```lua
require("scwsserver")
local xdbPath	= "dict.xdb"
local keywords = scwsserver.run(content,xdbPath)
for k,v in pairs(keywords) do
  ngx.say(k,v)
end
```

