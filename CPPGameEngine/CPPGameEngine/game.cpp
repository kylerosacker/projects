#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

//float player_pos_x = 0.f;

float player1_pos_y, player1_pos_dy, player1_pos_ddy;
float player2_pos_y, player2_pos_dy, player2_pos_ddy;

float arena_half_size_x = 85;
float arena_half_size_y = 45;

float player1_half_size_x = 2.5;
float player2_half_size_x = 2.5;
float player1_half_size_y = 12;
float player2_half_size_y = 12;

float ball_pos_x, ball_pos_y, ball_pos_dx = 100, ball_pos_dy = 100;
float ball_half_size_x = 1;
float ball_half_size_y = 1;

float speed = 2000.f;

internal void simulate_game(Input * input, float dt){
	clear_screen(0xff5500);
	draw_rect(0, 0, arena_half_size_x, arena_half_size_y, 0xffaa33);

	player1_pos_ddy = 0.f;
	player2_pos_ddy = 0.f;

	if (pressed(BUTTON_SPEEDUP)) speed += 1;
	if (pressed(BUTTON_SPEEDDOWN)) speed -= 1;
	if (is_down(BUTTON_UP)) player1_pos_ddy += speed;
	if (is_down(BUTTON_DOWN)) player1_pos_ddy -= speed;
	if (is_down(BUTTON_W)) player2_pos_ddy += speed;
	if (is_down(BUTTON_S)) player2_pos_ddy -= speed;
	//if (pressed(BUTTON_LEFT)) player_pos_x -= speed;
	//if (pressed(BUTTON_RIGHT)) player_pos_x += speed;

	player1_pos_ddy -= player1_pos_dy * 15.f;
	player1_pos_dy = player1_pos_dy + player1_pos_ddy * dt;
	player1_pos_y = player1_pos_y + player1_pos_dy * dt + player1_pos_ddy * dt * dt * .5f;
	
	if (player1_pos_y + player1_half_size_y > arena_half_size_y) {
		player1_pos_y = arena_half_size_y - player1_half_size_y;
		player1_pos_dy *= -1;
	}

	if (player1_pos_y - player1_half_size_y < -arena_half_size_y) {
		player1_pos_y = -arena_half_size_y + player1_half_size_y;
		player1_pos_dy *= -1;
	}

	player2_pos_ddy -= player2_pos_dy * 20.f;
	player2_pos_dy = player2_pos_dy + player2_pos_ddy * dt;
	player2_pos_y = player2_pos_y + player2_pos_dy * dt + player2_pos_ddy * dt * dt * .5f;

	if (player2_pos_y + player1_half_size_y > arena_half_size_y) {
		player2_pos_y = arena_half_size_y - player2_half_size_y;
		player2_pos_dy *= -1;
	}

	if (player2_pos_y - player2_half_size_y < -arena_half_size_y) {
		player2_pos_y = -arena_half_size_y + player2_half_size_y;
		player2_pos_dy *= -1;
	}
	
	ball_pos_y = ball_pos_y + ball_pos_dy * dt;
	ball_pos_x = ball_pos_x + ball_pos_dx * dt;

	if (ball_pos_y + ball_half_size_y > arena_half_size_y) {
		ball_pos_y = arena_half_size_y - ball_half_size_y;
		ball_pos_dy *= -1;
	}

	if (ball_pos_y - ball_half_size_y < -arena_half_size_y) {
		ball_pos_y = -arena_half_size_y + ball_half_size_y;
		ball_pos_dy *= -1;
	}

	if (ball_pos_x + ball_half_size_x > arena_half_size_x) {
		ball_pos_x = arena_half_size_x - ball_half_size_x;
		ball_pos_dx *= -1;
	}

	if (ball_pos_x - ball_half_size_x < -arena_half_size_x) {
		ball_pos_x = -arena_half_size_x + ball_half_size_x;
		ball_pos_dx *= -1;
	}

	//draw_rect(player_pos_x, player_pos_y, 1, 1, 0x00f200);
	
	draw_rect(ball_pos_x, ball_pos_y, ball_half_size_x, ball_half_size_y, 0xffffff);
	draw_rect(80, player1_pos_y, player1_half_size_x, player1_half_size_y, 0xff00ff);
	draw_rect(-80, player2_pos_y, player2_half_size_x, player2_half_size_y, 0x00ffff);
}