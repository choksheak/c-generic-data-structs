VERSION    = 1.0
LIBEXT     = dll

CC         = gcc
CFLAGS     = -Wall -pedantic -std=c99 -g3
CRELFLAGS  = -Wall -pedantic -std=c99 -Os -s -DNDEBUG
SRCDIR     = src
OBJDIR     = obj
TESTDIR    = test
TESTOBJDIR = testobj
BINDIR     = bin

LIBNAME    = gr-data-structs
TARGET     = $(BINDIR)/lib$(LIBNAME).$(LIBEXT)
RELTARGET  = $(BINDIR)/lib$(LIBNAME)-$(VERSION).$(LIBEXT)
TESTEXE	   = $(BINDIR)/test_main.exe
SRCS       = ${wildcard $(SRCDIR)/*.c}
TESTS      = ${wildcard $(TESTDIR)/*.c}
OBJS       = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TESTOBJS   = $(TESTS:$(TESTDIR)/%.c=$(TESTOBJDIR)/%.o)

all: test rel

print:
	@echo SRCS     = $(SRCS)
	@echo OBJS     = $(OBJS)
	@echo TESTOBJS = $(TESTOBJS)
	@echo TARGET   = $(TARGET)
	@echo TESTEXE  = $(TESTEXE)

obj: $(OBJS) $(TESTOBJS)

$(OBJDIR)/%.o: $(SRCS)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $(@:$(OBJDIR)%.o=$(SRCDIR)%.c) -o $@

$(TESTOBJDIR)/%.o: $(TESTS)
	@mkdir -p $(TESTOBJDIR)
	$(CC) $(CFLAGS) -I$(SRCDIR) -D GR_TEST -c $(@:$(TESTOBJDIR)%.o=$(TESTDIR)%.c) -o $@

lib: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -shared -o $(TARGET) $(OBJS)

exe: $(TESTEXE)

$(TESTEXE): $(TARGET) $(TESTOBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -L$(BINDIR) -l$(LIBNAME) -o $(TESTEXE) $(TESTOBJS)

test: $(TESTEXE)
	./$(TESTEXE)

rel: $(RELTARGET)

$(RELTARGET): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CC) $(CRELFLAGS) -shared -o $(RELTARGET) $(OBJS)

clean:
	rm -rf $(TARGET) $(BINDIR) $(OBJDIR) $(TESTOBJDIR)
