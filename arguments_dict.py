arguments_dict = {
    'genmc-xmm' :  ['--v1', '--XMM'],
    'genmc' :      ['--v1', '--disable-race-detection', '--disable-instruction-caching'],
    'genmc-wkmo' : ['--wkmo', '--mo', '--count-duplicate-execs', '--disable-race-detection'],
    'genmc-old' :  ['--rc11', '--mo', '--count-duplicate-execs', '--disable-race-detection'],
    'genmc-imm' : ['--imm', '--v1', '--disable-race-detection', '--disable-instruction-caching']
}
