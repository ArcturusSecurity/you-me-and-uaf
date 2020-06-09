# You, me and Use-After-Free
Example code to demonstrate a Use-after-Free issue. Just run `make` and then
run the demo binary; `./demo2`.

## Disabling ASLR
Run the following as root to disable all ASLR:
`sysctl -w kernel.randomize_va_space=0`

## Re-enabling ASLR
Run the following as root to re-enable ASLR:
`sysctl -w kernel.randomize_va_space=2`

# Play along
Compile the demo2 example binary and run it through `gdb`. Following that, load
the `gdb.breakpoints` for some helpful breakpoints and run the binary with 
`run <crafted_input`.

Can you nanage to get the executable to run 'exploit', or your own code? :) 
If you do, reach out and say hello@arcturus.net
