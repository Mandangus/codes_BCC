#
# Codigo Assembly MIPS para um Hello World.
# Le um inteiro do teclado e verifica se nr < 0
# Se nr < 0 imprime a string Hello World --! seguida do nr digitado
# Se nr >=0 imprime a string Hello World ++! seguida do nr digitado
#
#

	.data				# inicia segmento de dados
	.align 0			# alinhamento a byte (2^0)
str_dig: .asciiz "Digite o numero: " 	# definindo a string str_dig
str_pos: .asciiz "\nHello World ++! " 	# definindo a string str_pos
str_neg: .asciiz "\nHello World --! " 	# definindo a string str_neg

	.text				# inicia segmento de texto (instrucoes)
	.globl main			# rotulo main e global

main:					# inicio do programa

	# vai imprimir uma string
	# load immediate
	li $v0, 4			# atribui 4 para $v0. Codigo para print_str
	# load address
	la $a0, str_dig			# carrega endereco de str_dig em $a0
					# eh o end da string a ser impressa
	syscall				# chamada de sistema para E/S
	
	# vai ler um inteiro vindo do teclado
	li $v0, 5			# atribui 5 para $vo. Codigo para read_int
	syscall				# chamada de sistema para E/S. Retorno estara em $v0
	move $t2, $v0			# copia conteudo digitado para $t2 para preservar dado
	
	# blt - branch if less than - desvia para o label "print_neg" se $t2 ? menor que $zero, ou seja, se ? negativo
	blt $t2, $zero, print_neg
	
	# vai imprimir uma string
	li $v0, 4			# atribui 4 para $v0. Codigo para print_str
	la $a0, str_pos			# carrega endereco de str_pos em $a0
					# eh o end da string a ser impressa
	syscall				# chamada de sistema para E/S

	# vai imprimir um inteiro se ele for >= 0 
	li $v0, 1			# atribui 1 para $v0. Codigo para print_int
	move $a0, $t2			# copia nr a ser impresso para $a0.
					# argumento de entrada para a impressao do int
	syscall				# chamada de sistema para E/S
	
	# jump
	j thatsallfolks			# goto thatsallfolks. Salta a impressao do nr negativo
	
print_neg:				# aqui fara impressao no nr negativo
 
	# vai imprimir uma string
	li $v0, 4			# atribui 4 para $v0. Codigo para print_str
	la $a0, str_neg			# carrega endereco de str_neg em $a0
					# eh o end da string a ser impressa
	syscall				# chamada de sistema para E/S
	
	# vai imprimir um inteiro
	li $v0, 1			# atribui 1 para $v0. Codigo para print_int
	move $a0, $t2			# copia nr a ser impresso para $a0.
					# argumento de entrada para a impressao do int
	syscall				# chamada de sistema para E/S
		
thatsallfolks:				# o que que ha velhinho?
	li $v0, 10			# atribui 10 para $v0. Codigo para exit (termina programa)
	syscall				# chamada de sistema para E/S