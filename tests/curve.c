#include "test.h"

void test(){
	VkvgContext ctx = vkvg_create(surf);

	vkvg_set_fill_rule(ctx, VKVG_FILL_RULE_NON_ZERO);
	vkvg_set_line_width(ctx, 20);

	vkvg_scale(ctx,2,2);
	vkvg_set_line_join(ctx, VKVG_LINE_JOIN_BEVEL);

	//vkvg_arc (ctx, 200, 500, 100, 0, M_PI);

	vkvg_set_source_rgb   (ctx, 0.5f,0,0);


	/*vkvg_move_to(ctx,100,100);
	vkvg_line_to(ctx,300,100);
	vkvg_line_to(ctx,500,300);
	vkvg_line_to(ctx,300,500);
	//vkvg_arc (ctx, 200, 500, 100, 0, M_PI);
	vkvg_line_to(ctx,300,700);
	vkvg_line_to(ctx,100,500);*/

	/*vkvg_arc(ctx, 300, 300, 100, 0, M_PI);
	vkvg_line_to(ctx,100,200);
	vkvg_line_to(ctx,200,100);
	vkvg_arc(ctx, 250, 100, 50, M_PI, M_PI * 1.5f);
	vkvg_line_to(ctx,350,50);
	vkvg_arc(ctx, 350, 100, 50, M_PI*1.5f, M_PI * 2.0f);

	vkvg_stroke(ctx);
	vkvg_translate(ctx,400,30);

	*/
	//vkvg_set_fill_rule(ctx,VKVG_FILL_RULE_EVEN_ODD);
	vkvg_translate(ctx,200,30);
	vkvg_arc(ctx, 200, 200, 20, 0, M_PIF*2);
	//vkvg_stroke(ctx);

	vkvg_set_source_rgba (ctx, 0.5f,0.0f,1.0f,0.5f);
	vkvg_move_to(ctx,100,100);
	vkvg_line_to(ctx,200,100);
	//vkvg_move_to(ctx,200,100);
	vkvg_curve_to(ctx,250,100,300,150,300,200);
	vkvg_line_to(ctx,300,300);
	vkvg_curve_to(ctx,300,350,250,400,200,400);
	vkvg_line_to(ctx,100,400);
	vkvg_curve_to(ctx,50,400,10,350,10,300);
	vkvg_line_to(ctx,10,200);
	vkvg_curve_to(ctx,10,150,50,100,100,100);
	//vkvg_close_path(ctx);
	vkvg_fill_preserve(ctx);
	vkvg_set_source_rgba   (ctx, 0.1f,0.3f,0.7f,0.5f);
	vkvg_stroke(ctx);


	vkvg_destroy(ctx);
}

void curved_rect() {
	VkvgContext ctx = vkvg_create(surf);

	float x = 50, y = 50, width = 150, height = 140, radius = 30;

	vkvg_scale(ctx, 2, 2);
	//vkvg_rotate(ctx,0.5f);

	vkvg_set_line_width(ctx, 15);
	vkvg_set_source_rgba(ctx, 0, 0.5f, 0.4f, 1);

	if ((radius > height / 2) || (radius > width / 2))
		radius = MIN(height / 2, width / 2);

	vkvg_move_to(ctx, x, y + radius);
	vkvg_arc(ctx, x + radius, y + radius, radius, M_PIF, (float)-M_PI_2);
	vkvg_line_to(ctx, x + width - radius, y);
	vkvg_arc(ctx, x + width - radius, y + radius, radius, (float)-M_PI_2, 0);
	vkvg_line_to(ctx, x + width, y + height - radius);
	vkvg_arc(ctx, x + width - radius, y + height - radius, radius, 0, (float)M_PI_2);
	vkvg_line_to(ctx, x + radius, y + height);
	vkvg_arc(ctx, x + radius, y + height - radius, radius, (float)M_PI_2, M_PIF);
	vkvg_line_to(ctx, x, y + radius);
	vkvg_close_path(ctx);
	vkvg_fill_preserve(ctx);
	vkvg_set_source_rgba(ctx, 0.5f, 0, 0, 0.5f);
	vkvg_stroke(ctx);

	vkvg_destroy(ctx);
}

void test2() {
	VkvgContext ctx = vkvg_create(surf);

	vkvg_move_to(ctx, 100, 400);
	vkvg_curve_to(ctx, 100, 100, 600, 700, 600, 400);
	vkvg_curve_to(ctx, 1000, 100, 100, 800, 1000, 800);
	vkvg_curve_to(ctx, 1000, 500, 700, 500, 700, 100);
	vkvg_close_path(ctx);

	//vkvg_set_source_rgba   (ctx, 0.5,0.0,1.0,0.5);
	//vkvg_fill_preserve(ctx);

	vkvg_set_source_rgba(ctx, 1, 0, 0, 1);
	vkvg_set_line_width(ctx, 40);
	vkvg_stroke(ctx);

	vkvg_destroy(ctx);
}

static float line_width = 1.f;
static vkvg_line_cap_t line_cap = VKVG_LINE_CAP_ROUND;
static vkvg_fill_rule_t fill_rule = VKVG_FILL_RULE_NON_ZERO;
static float dashes[] = {30.0f, 10.0f};
static uint32_t dashes_count = 0;
static bool fillAndStroke = true;

void _rnd_curve (VkvgContext ctx) {
	float w = (float)test_width;
	float h = (float)test_height;

	float x2 = w*rand()/RAND_MAX;
	float y2 = h*rand()/RAND_MAX;
	float cp_x1 = w*rand()/RAND_MAX;
	float cp_y1 = h*rand()/RAND_MAX;
	float cp_x2 = w*rand()/RAND_MAX;
	float cp_y2 = h*rand()/RAND_MAX;

	vkvg_curve_to(ctx, cp_x1, cp_y1, cp_x2, cp_y2, x2, y2);
}

VkvgContext _initCtx() {
	VkvgContext ctx = vkvg_create(surf);
	vkvg_clear(ctx);
	vkvg_set_line_width (ctx,line_width);
	vkvg_set_line_cap(ctx, line_cap);
	vkvg_set_dash (ctx, dashes, dashes_count, 0);
	return ctx;
}

void random_curves () {
	float w = (float)test_width;
	float h = (float)test_height;

	VkvgContext ctx = _initCtx();

	for (uint32_t i=0; i<test_size; i++) {
		randomize_color(ctx);
		float x1 = w*rand()/RAND_MAX;
		float y1 = h*rand()/RAND_MAX;

		vkvg_move_to (ctx, x1, y1);
		_rnd_curve(ctx);

		vkvg_stroke (ctx);
	}
	vkvg_destroy(ctx);
}
void single_long_line_curved () {
	float w = (float)test_width;
	float h = (float)test_height;

	VkvgContext ctx = _initCtx();
	vkvg_set_fill_rule(ctx, fill_rule);

	randomize_color(ctx);
	float x1 = w*rand()/RAND_MAX;
	float y1 = h*rand()/RAND_MAX;
	vkvg_move_to (ctx, x1, y1);

	for (uint32_t i=0; i<test_size; i++) {
		_rnd_curve(ctx);
	}

	if (fillAndStroke) {
		vkvg_fill_preserve(ctx);
		randomize_color(ctx);
		vkvg_stroke (ctx);
	}else
		vkvg_fill (ctx);

	vkvg_destroy(ctx);
}
int main(int argc, char *argv[]) {
	PERFORM_TEST(test, argc, argv);
	PERFORM_TEST(test2, argc, argv);
	PERFORM_TEST(curved_rect, argc, argv);
	fillAndStroke = false;
	fill_rule = VKVG_FILL_RULE_NON_ZERO;
	PERFORM_TEST(single_long_line_curved, argc, argv);
	fill_rule = VKVG_FILL_RULE_EVEN_ODD;
	PERFORM_TEST(single_long_line_curved, argc, argv);
	fillAndStroke = true;
	fill_rule = VKVG_FILL_RULE_NON_ZERO;
	PERFORM_TEST(single_long_line_curved, argc, argv);
	fill_rule = VKVG_FILL_RULE_EVEN_ODD;
	PERFORM_TEST(single_long_line_curved, argc, argv);

	PERFORM_TEST(random_curves, argc, argv);
	return 0;
}
