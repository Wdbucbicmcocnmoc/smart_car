

NAME MDU32

$include (STC16Fxx.H)

;-----------------------------------------------------------------------------
; 'LMUL' Long Integer Multiplication function replacement
;-----------------------------------------------------------------------------
?PR?LMUL?MDU  SEGMENT CODE
  PUBLIC  ?C?LMUL    
  RSEG    ?PR?LMUL?MDU
?C?LMUL:
  MOV     DMAIR,#0x02   
  RET

;-----------------------------------------------------------------------------
; 'ULDIV' Unsigned Long Integer Division function replacement
;-----------------------------------------------------------------------------
?PR?ULDIV?MDU  SEGMENT CODE
  PUBLIC  ?C?ULDIV    
  RSEG    ?PR?ULDIV?MDU
?C?ULDIV:
ULDIV:
  MOV     DMAIR,#0x04   
  RET

;-----------------------------------------------------------------------------
; 'SLDIV' Signed Long Integer division function replacement
;-----------------------------------------------------------------------------
?PR?SLDIV?MDU  SEGMENT CODE
  PUBLIC  ?C?SLDIV    
  RSEG    ?PR?SLDIV?MDU
?C?SLDIV:
  MOV     DMAIR,#0x06   
  RET

END
