SRC := main.c lib.c content_type.c status.c url.c request.c \
       response.c list.c process.c
jim_web: $(SRC)
	gcc -g -Wno-write-strings $(SRC) -o web
clean:
	rm -f web
