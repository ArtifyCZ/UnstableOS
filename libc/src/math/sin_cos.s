.global cos
.type cos,@function
cos:
    fldl 4(%esp)
    fcos
    ret
.global cosf
.type cosf,@function
cosf:
    flds 4(%esp)
    fcos
    ret
.global cosl
.type cosl,@function
cosl:
    fldt 4(%esp)
    fcos
    ret

.global sin
.type sin,@function
sin:
    fldl 4(%esp)
    fsin
    ret
.global sinf
.type sinf,@function
sinf:
    flds 4(%esp)
    fsin
    ret
.global sinl
.type sinl,@function
sinl:
    fldt 4(%esp)
    fsin
    ret

.global sincos
.type sincos,@function
sincos:
    fldl 4(%esp)
    fsincos
    movl 0xC(%esp), %ecx
    movl 0x10(%esp), %edx
    fstpl (%edx)
    fstpl (%ecx)
    ret
.global sincosf
.type sincosf,@function
sincosf:
    flds 4(%esp)
    fsincos
    movl 0x8(%esp), %ecx
    movl 0xC(%esp), %edx
    fstpl (%edx)
    fstpl (%ecx)
    ret
.global sincosl
.type sincosl,@function
sincosl:
    fldt 4(%esp)
    fsincos
    movl 0x10(%esp), %ecx
    movl 0x14(%esp), %edx
    fstpl (%edx)
    fstpl (%ecx)
    ret