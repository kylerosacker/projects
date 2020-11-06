#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

//float player_pos_x = 0.f;

u32 player1_score = 0;
u32 player2_score = 0;

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


internal void simulate_player(float *p, float *dp, float ddp, float dt, float half_size) {
	ddp -= *dp * 15.f;
	*dp = *dp + ddp * dt;
	*p = *p + *dp * dt + ddp * dt * dt * .5f;

	if (*p + half_size > arena_half_size_y) {
		*p = arena_half_size_y - half_size;
		*dp *= -1;
	}

	if (*p - half_size < -arena_half_size_y) {
		*p = -arena_half_size_y + half_size;
		*dp *= -1;
	}
}

internal bool has_collided(float p1x, float p1y, float hs1x, float hs1y,
	float p2x, float p2y, float hs2x, float hs2y) {
	return (p1x + hs1x > p2x - hs2x &&
		p1x - hs1x < p2x + hs2x &&
		p1y + hs1y > p2y - hs2y &&
		p1y - hs1y < p2y + hs2y);
}
internal void simulate_game(Input* input, float dt) {
	clear_screen(0xff5500);
	draw_rect(0, 0, arena_half_size_x, arena_half_size_y, 0xffaa33);
	show_score_player1(player1_score);
	show_score_player2(player2_score);

	player1_pos_ddy = 0.f;
	player2_pos_ddy = 0.f;

	/*if (pressed(BUTTON_SPEEDUP)) {
		ball_pos_dx += 10;
		ball_pos_dy += 10;
	}*/
	if (pressed(BUTTON_SPEEDDOWN)) speed -= 1;
	if (is_down(BUTTON_UP)) player1_pos_ddy += speed;
	if (is_down(BUTTON_DOWN)) player1_pos_ddy -= speed;
	if (is_down(BUTTON_W)) player2_pos_ddy += speed;
	if (is_down(BUTTON_S)) player2_pos_ddy -= speed;
	//if (pressed(BUTTON_LEFT)) player_pos_x -= speed;
	//if (pressed(BUTTON_RIGHT)) player_pos_x += speed;

	simulate_player(&player1_pos_y, &player1_pos_dy, player1_pos_ddy, dt, player1_half_size_y);
	simulate_player(&player2_pos_y, &player2_pos_dy, player2_pos_ddy, dt, player2_half_size_y);

	//Simulate Ball
	{
		ball_pos_y = ball_pos_y + ball_pos_dy * dt;
		ball_pos_x = ball_pos_x + ball_pos_dx * dt;


		//ball arena collisions
		if (ball_pos_y + ball_half_size_y > arena_half_size_y) {
			ball_pos_y = arena_half_size_y - ball_half_size_y;
			ball_pos_dy *= -1;
		}

		if (ball_pos_y - ball_half_size_y < -arena_half_size_y) {
			ball_pos_y = -arena_half_size_y + ball_half_size_y;
			ball_pos_dy *= -1;
		}

		if (ball_pos_x + ball_half_size_x > arena_half_size_x) {
			player1_score += 1;
			ball_pos_x = 0;
			ball_pos_y = 0;
			ball_pos_dx *= -1;
			ball_pos_dy = 0;

		}

		if (ball_pos_x - ball_half_size_x < -arena_half_size_x) {
			player2_score += 1;
			ball_pos_x = 0;
			ball_pos_y = 0;
			ball_pos_dx *= -1;
			ball_pos_dy = 0;

		}

		//ball player collisions
		if (has_collided(ball_pos_x, ball_pos_y, ball_half_size_x, ball_half_size_y, 80, player1_pos_y, player1_half_size_x, player1_half_size_y)) {
			ball_pos_dx *= -1;
			ball_pos_dy = (ball_pos_y - player1_pos_y) * 2 + player1_pos_dy * .75f;
		}
		if (has_collided(ball_pos_x, ball_pos_y, ball_half_size_x, ball_half_size_y, -80, player2_pos_y, player2_half_size_x, player2_half_size_y)) {
			ball_pos_dx *= -1;
			ball_pos_dy = (ball_pos_y - player2_pos_y) * 2 + player2_pos_dy * .75f;
		}
	}

	//Render ball, paddles
	draw_rect(ball_pos_x, ball_pos_y, ball_half_size_x, ball_half_size_y, 0xffffff);
	draw_rect(80, player1_pos_y, player1_half_size_x, player1_half_size_y, 0xff00ff);
	draw_rect(-80, player2_pos_y, player2_half_size_x, player2_half_size_y, 0x00ffff);
}