.text
.global set_batt_from_ports
set_batt_from_ports:
    ## assembly instructions here

    ## a useful technique for this problem
    # movX some_global_var(%rip),%reg

.data
my_int:
    .int 1234

other_int:
    .int 0b0101

my_array:
    .int 10
    .int 0x00014
    .int 0b11110

.text
.global set_display_from_batt
set_display_from_batt:
    ## assembly instructions here

    ## two useful techniques for this problem
    # movl my_int(%rip),%eax
    # leaq my_array(%rip),%rdx  #load pointer to beginning of my_array into rdx

.text
.global batt_update
batt_update:
    ## assembly instructions here
