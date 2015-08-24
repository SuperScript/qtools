www:
	package/create compile-doc doc build target `awk '$$1{print $$1}' < doc/build=d`
	cp dist/qtools-0.56.tar.gz www/


.PHONY: www
