arguments_dict = {
    'genmc-xmm' :  ['--v1', '--disable-sr', '--XMM'], # disable-sr is there bc genmc-old does not have it, so it's more fair this way
    'genmc' :      ['--v1', '--disable-sr', '--disable-race-detection', '--disable-instruction-caching'],
    'genmc-wkmo' : ['--wkmo', '--mo', '--count-duplicate-execs', '--disable-race-detection'],
    'genmc-old' :  ['--rc11', '--mo', '--count-duplicate-execs', '--disable-race-detection'],
    'genmc-imm' : ['--imm', '--v1', '--disable-sr', '--disable-race-detection', '--disable-instruction-caching']
}
