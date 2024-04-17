.PHONY: testimage


testimage : $(SRC_DIR)/main.o $(SRC_DIR)/RAG.o $(SRC_DIR)/merge.o $(SRC_DIR)/moment.o
	$(CC)  $^ -o $(BIN_DIR)/$@ $(LDFLAGS) 

$(SRC_DIR)/main.o : $(SRC_DIR)/main.c 
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ -c

$(SRC_DIR)/RAG.o : $(SRC_DIR)/RAG.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ -c
	
$(SRC_DIR)/merge.o : $(SRC_DIR)/merge.c 
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ -c
	
$(SRC_DIR)/moment.o : $(SRC_DIR)/moment.c 
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $^ -c
