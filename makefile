# gcc -v 添加详细输出 
UV_FLAGS=-I/d/vscodeProject/HttpTest/libuv/include -L/d/chromeDownloads/libuv-v1.34.2/build -luv_a
CURL_FLAGS=-I/d/chromeDownloads/curl-8.5.0_6-win64-mingw/include -L/d/chromeDownloads/curl-8.5.0_6-win64-mingw/lib -lcurl
objs1 := ini.o httptest.o 
objs2 := ini.o get_header_and_body.o
objs3 := ini.o post_test.o 
#httptest: $(objs1)
#gcc -o httptest $^ $(UV_FLAGS) $(CURL_FLAGS) -Wl,-rpath,'$$ORIGIN'
#header_and_body:$(objs2)
post_test :$(objs3)
	gcc -o post_test $^ $(UV_FLAGS) $(CURL_FLAGS) -Wl,-rpath,'$$ORIGIN'
%.o : %.c
	gcc -c -g $(UV_FLAGS) $(CURL_FLAGS) $< -o $@ 

clean: 
	rm *.o  post_test -f 
