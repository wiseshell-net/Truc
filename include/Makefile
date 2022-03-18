
.PHONY:
all:
	$(MAKE) -C ..

%:
	$(MAKE) -C .. $@

%.o: %.h*
	$(MAKE) -C .. src/$@

%.o: %.[cC]*
	$(MAKE) -C .. src/$@
