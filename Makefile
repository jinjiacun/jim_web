SRC := main.c lib.c content_type.c status.c url.c request.c \
       response.c list.c process.c cgi.c
jim_web: $(SRC)
	gcc -pg -g -w $(SRC) -o web
clean:
	rm -f web
