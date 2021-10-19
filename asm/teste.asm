	.data
	.align 0
in_base: .asciiz "Digite a base do numero a ser convertido (B para binário, D para decimal, H para hexadecimal): "
in_num: .asciiz "Digite o numero a ser convertido: "
in_newbase: .asciiz "Digite a nova base do numero (B para binário, D para decimal, H para hexadecimal): "
in_debugD: .asciiz "Estamos convertendo a partir do Decimal"
in_debugH: .asciiz "Estamos convertendo a partir do Hexadecimal"
in_debugB: .asciiz "Estamos convertendo a partir do Binario"
out_number1: .asciiz "O numero "
out_number2: .asciiz " de base "
out_number3: .asciiz " eh "
out_number4: .asciiz " na base "

input_number: .space 32
output_number: .space 32

	.text
	.globl main
main:
	li $v0, 4			#Código para print_string
	la $a0, in_base			#in_base será a string printada
	syscall
	
	li $v0, 12			#Código para read_char (ler a base)
	syscall
	
	move $s0, $v0			#Salva o char lido (base de entrada) no registrador $s0
	
	jal print_newline
	
	li $v0, 4			#Código para print_string
	la $a0, in_num			#in_num será a string printada
	syscall

   	li $v0, 8       		# Código para read_string
   	la $a0, input_number  		# carrega o espaço de bytes no endereço input_number
   	li $a1, 32     			# aloca os 32 bytes para a string
   	move $s1, $a0  			# salva o "numero" lido em $s1
   	syscall
	
   	move $t0, $s1   		# copia o numero lido para $t0
	
	li $v0, 4			#Código para print_string
	la $a0, in_newbase		#in_novabase será a string printada
	syscall
	
	li $v0, 12			#Código para read_char (ler a nova base)
	syscall
	
	move $s2, $v0			#Salva o numero lido (nova base) no registrador $s2
	
	jal print_newline
	
	beq $s0, 'D', fromDecimal
	beq $s0, 'H', fromHexa
	beq $s0, 'B', fromBin
	
#########################  FUNCOES A PARTIR DO DECIMAL ###############################	
fromDecimal:
	li $v0, 4
	la $a0, in_debugD
	syscall
	jal print_newline
	j fim
#########################   FUNCOES A PARTIR DO HEXA   ###############################
fromHexa:
	li $v0, 4
	la $a0, in_debugH
	syscall
	jal print_newline
	beq $s2, 'B',toBin_H
	beq $s2, 'D',toDec_H
	j fim

toBin_H:
	 

toDec_H:
	la $t0, ($s1)
	lbu $t1, ($t0)
	ble $t1, '9', 

#########################  FUNCOES A PARTIR DO BINARIO ###############################
fromBin:
	li $v0, 4
	la $a0, in_debugB
	syscall
	jal print_newline
	j fim
print_newline:
	li $v0, 11
	li $a0, '\n'
	syscall
	jr $ra

fim:
	li $v0, 1			    #Código para print_string
	la $a0, 0($s2)			#in_base será a string printada
	syscall

	li $v0, 10			# 10 é código para o fim do programa
	syscall
