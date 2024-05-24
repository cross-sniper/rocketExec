#!/usr/bin/env rocket
--[[
all colors are lowercase 

todas as cores estão em lowercase


the main function is called by rocket

a função main é chamada pelo rocketExec(rocket)


rocket is a game runtime for linux desktop
it uses lua as the programming language

rocket é uma runtime de jogos pra linux desktop
usando lua como a linguagem de programação


tutorial 1: moving and drawing a cube

tutorial 1: movendo e desenhando um cubo

]]

-- position, width,height
-- posição, largura, altura
x = 400
y = 300
w = 20
h = 20
--[[
	400, 300
	are the center of the window
	é o centro da janela
]]

-- main loop
-- loop principal
function loop(dt)
 	--[[
 		code to handle player movement
 		codigo pra lidar com movimento do player

 		always multiply by DT to make sure the player doesn't move too fast
 		sempre multiplique por DT(DeltaTime) pra ter certeza de que o player não se mova muito rapido

		dt always is recalculated betwen frames, dt meaning:
		dt sempre é recauculado entre frames, significado dt:

		 "elapsed time since the game last updated, which will vary depending on the speed of the computer, and how much work needs to be done in the program at any given time."
		"Tempo decorrido desde a última atualização do jogo, que varia dependendo da velocidade do computador e de quanto trabalho precisa ser feito no programa a qualquer momento."
		 - wikipedia
 	]]
	if IsKeyDown(KEY_W) then y = y - 200 * dt end
	if IsKeyDown(KEY_S) then y = y + 200 * dt end
	if IsKeyDown(KEY_A) then x = x - 200 * dt end
	if IsKeyDown(KEY_D) then x = x + 200 * dt end

	--[[
		draws the player
		desenha o player
	]]
    DrawRectangle(x, y, w, h, white)
end

function main()
	--[[
		this initializes the whole game window, enabling us to actualy do something
		Isso inicializa toda a janela do jogo, permitindo-nos realmente fazer algo
	]]
    InitWindow(800, 600, "exemple 1 | exemplo 1")

    --[[
    	WindowShouldClose only returns true if the exit key(wich will allways be ESC, since i havent added the option to change it yet), is pressed, otherwise, returns false
    	we do "while not" to invert the value, so this is a infinite loop

    	WindowShouldClose só retorna true se a tecla exit (que será ESC, já que ainda não adicionei a opção de alterá-la), for pressionada, caso contrário, retornará false
    	fazemos "while not" para inverter o valor, então este é um loop infinito
    ]]
    while not WindowShouldClose() do
    	--[[
    		makes the functions related to drawing work

    		faz as funções relacionadas a desenhar, ser capazes de functionar
    	]]
        BeginDrawing()

        --[[
         	clears the background with the color black
	        limpa o plano de fundo com a cor preta
        ]]
        ClearBackground(black)

        --[[
        	this sets the dt to be the DeltaTime
        	isso da o valor do DeltaTime para a variavel dt
        ]]
        dt = GetFrameTime()

		--[[
			calls the loop function with dt as a argument
			chama a função loop com o valor do dt como um argumento
		]]
        loop(dt)
        --[[
        	stops drawing and makes everything visible on the screen
        	termina de desenhar, e faz tudo ser visivel na tela
        ]]
        EndDrawing()
    end
    --[[
    	closes the window once we are out of the loop
    	fecha a janela quando sair do loop
    ]]
    CloseWindow()
end
