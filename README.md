Some experiments to create minimal executables for Linux without any
libc, nor assembly files.  Yes there must be some inline assembly to
interact with Linux syscalls, but all program logics are in a high
level language; C for now, Rust under consideration.

Such tools may be of interest when
- used in containers for minimal overhead, or
- some native code are needed by sysop shell scripts to perform a few
  syscalls in a specific setting not exposed by standard tools; if the
  programs are tiny they can be "gzip | base64" encoded and embedded
  directly in the shell script.

As an example `pause.c` implements a command similar to the one used
by `docker://k8s.gcr.io/pause`; on my machine this compiles to an
executable of size 744 BYTES.

I have not yet decided which license I'd like to release these under,
consider these code as "license unclear" for now.  For sure I would
choose a permissive license if anyone shows interest in them.
