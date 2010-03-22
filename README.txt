Nugroho Free Hash Tools (NFHT)

* SHA tools: sha1sum, sha224sum, sha256sum, sha384sum, sha512sum
*  MD tools:  md4sum,    md5sum
* RMD tools: rmd128sum, rmd160sum

Requirement:

The application utilize NFHL (Nugroho Free Hash Library) to generate
message hash. In order to compile properly, the NFHL variable must be
point to correct NFHL location, as in the Makefile example: NFHL is
assigned to ../nfhl which assuming that the library were located and
compiled at this location.
