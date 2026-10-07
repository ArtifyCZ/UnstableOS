// TODO: redo when fenv exception setting

__restore_rounding:
    movw %ax, -4(%esp)
    fldcw -4(%esp)
    ret

__set_round_nearest:
    fstcw -4(%esp)
    movw -4(%esp), %ax
    movw $0x67f, -4(%esp)
    fldcw -4(%esp)
    ret

__set_round_down:
    fstcw -4(%esp)
    movw -4(%esp), %ax
    movw $0xe7f, -4(%esp)
    fldcw -4(%esp)
    ret

__set_round_up:
    fstcw -4(%esp)
    movw -4(%esp), %ax
    movw $0x167f, -4(%esp)
    fldcw -4(%esp)
    ret

__set_round_zero:
    fstcw -4(%esp)
    movw -4(%esp), %ax
    movw $0x1e7f, -4(%esp)
    fldcw -4(%esp)
    ret

.global nearbyint
.type nearbyint,@function
nearbyint:
    fldl 4(%esp)
    frndint
    ret
.global nearbyintf
.type nearbyintf,@function
nearbyintf:
    flds 4(%esp)
    frndint
    ret
.global nearbyintl
.type nearbyintl,@function
nearbyintl:
    fldt 4(%esp)
    frndint
    ret

.global floor
.type floor,@function
floor:
    fldl 4(%esp)
    call __set_round_down
    frndint
    call __restore_rounding
    ret

.global floorf
.type floorf,@function
floorf:
    flds 4(%esp)
    call __set_round_down
    frndint
    call __restore_rounding
    ret

.global floorl
.type floorl,@function
floorl:
    fldt 4(%esp)
    call __set_round_down
    frndint
    call __restore_rounding
    ret

.global ceil
.type ceil,@function
ceil:
    fldl 4(%esp)
    call __set_round_up
    frndint
    call __restore_rounding
    ret

.global ceilf
.type ceilf,@function
ceilf:
    flds 4(%esp)
    call __set_round_up
    frndint
    call __restore_rounding
    ret

.global ceill
.type ceill,@function
ceill:
    fldt 4(%esp)
    call __set_round_up
    frndint
    call __restore_rounding
    ret

.global trunc
.type trunc,@function
trunc:
    fldl 4(%esp)
    call __set_round_zero
    frndint
    call __restore_rounding
    ret

.global truncf
.type truncf,@function
truncf:
    flds 4(%esp)
    call __set_round_zero
    frndint
    call __restore_rounding
    ret

.global truncl
.type truncl,@function
truncl:
    fldt 4(%esp)
    call __set_round_zero
    frndint
    call __restore_rounding
    ret