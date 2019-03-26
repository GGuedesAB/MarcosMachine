pushdef(`int',`$1 DC  $2')dnl
define(`program',`  JMP var pushdef(`bgn', var)popdef(`var')
x DC  0
y DC  0
z DC  0
i DC  1')dnl
define(`begin',`bgn popdef(`tmp')LAD x')dnl
define(`ler',`  'INP $1)dnl
define(`escrever',`  OUT $1')dnl
define(`inc',`  LAD $1
  ADD i
  SAD $1')dnl
define(`dec',`  LAD $1
  SUB i
  SAD $1')dnl
define(`end',`  HLT  ')dnl
define(`end_program',`  END  ')dnl
define(`soma',`  LAD $2
  ADD $3
  SAD $1')dnl
define(`sub',`  LAD $2
  SUB $3
  SAD $1')dnl
define(`sub',`  LAD $2
  SUB $3
  SAD $1')dnl
define(`clr',`  LAD $1
  SUB $1
  SAD $1')dnl
define(`se',`  LAD $1
  ifelse($2, maior,
  SUB $3
  JZE var
  JLZ var,ifelse($2, menor,
  SUB $3
  JGZ var
  JZE var,
  SUB $3
  JLZ var
  JGZ var)) pushdef(`if', var)popdef(`var')')dnl
define(`end_se',`if popdef(`if')SAD z')dnl
define(`para',`  JMP var pushdef(`tmp', var)popdef(`var')
var pushdef(`cmp', var)popdef(`var')DC  $3
var pushdef(`cmp', var)popdef(`var')DC  $2
tmp popdef(`tmp')SAD z
  LAD cmp popdef(`cmp')
  SAD $1
var pushdef(`lop', var)popdef(`var')LAD $1
  SUB cmp popdef(`cmp')
  JZE var pushdef(`lev', var)popdef(`var')
  LAD $1
  ADD i
  SAD $1
  LAD z')dnl
define(`end_para',`  JMP lop popdef(`lop')
lev SAD x')dnl
define(`arranjo', $1 DS  $2)dnl
pushdef(`var', `a')dnl
pushdef(`var', `b')dnl
pushdef(`var', `c')dnl
pushdef(`var', `d')dnl
pushdef(`var', `e')dnl
pushdef(`var', `f')dnl
pushdef(`var', `g')dnl
pushdef(`var', `h')dnl
pushdef(`var', `j')dnl
pushdef(`var', `k')dnl
pushdef(`var', `l')dnl
pushdef(`var', `m')dnl
pushdef(`var', `n')dnl
pushdef(`var', `o')dnl
pushdef(`var', `p')dnl
pushdef(`var', `q')dnl
pushdef(`var', `r')dnl
pushdef(`var', `s')dnl
pushdef(`var', `t')dnl
pushdef(`var', `u')dnl
pushdef(`var', `v')dnl
pushdef(`var', `w')dnl
