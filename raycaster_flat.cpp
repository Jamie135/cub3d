#include <mlx.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600
#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define TILE_SIZE 64

typedef struct s_player {
  double x;
  double y;
  double dir_x;
  double dir_y;
  double plane_x;
  double plane_y;
} t_player;

int map[MAP_WIDTH][MAP_HEIGHT] = {
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
  {1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 1, 0, 1, 1, 1, 1, 0, 1},
  {1, 0, 1, 0, 1, 0, 0, 1, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
  {1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void draw_column(t_player *player, int col, int height, void *mlx_ptr, void *win_ptr) {
  int wall_height = HEIGHT / height;

  int wall_start = HEIGHT / 2 - wall_height / 2;
  int wall_end = HEIGHT / 2 + wall_height / 2;

  int tex_x = 0; // texture x-coordinate, you can implement texture mapping for more realistic rendering

  for (int y = 0; y < HEIGHT; y++) {
    if (y < wall_start)
      mlx_pixel_put(mlx_ptr, win_ptr, col, y, 0x6495ED); // Sky color
    else if (y >= wall_start && y <= wall_end)
      mlx_pixel_put(mlx_ptr, win_ptr, col, y, 0x808080); // Wall color
    else
      mlx_pixel_put(mlx_ptr, win_ptr, col, y, 0x008000); // Floor color
  }
}

void render(t_player *player, void *mlx_ptr, void *win_ptr) {
  for (int col = 0; col < WIDTH; col++) {
    double camera_x = 2 * col / (double)WIDTH - 1;
    double ray_dir_x = player->dir_x + player->plane_x * camera_x;
    double ray_dir_y = player->dir_y + player->plane_y * camera_x;

    int map_x = (int)player->x;
    int map_y = (int)player->y;

    double delta_dist_x = fabs(1 / ray_dir_x);
    double delta_dist_y = fabs(1 / ray_dir_y);

    double side_dist_x, side_dist_y;
    double perp_wall_dist;

    int step_x, step_y;
    int hit = 0;
    int side;

    if (ray_dir_x < 0) {
      step_x = -1;
      side_dist_x = (player->x - map_x) * delta_dist_x;
    } else {
      step_x = 1;
      side_dist_x = (map_x + 1.0 - player->x) * delta_dist_x;
    }

    if (ray_dir_y < 0) {
      step_y = -1;
      side_dist_y = (player->y - map_y) * delta_dist_y;
    } else {
      step_y = 1;
      side_dist_y = (map_y + 1.0 - player->y) * delta_dist_y;
    }

    while (!hit) {
      if (side_dist_x < side_dist_y) {
        side_dist_x += delta_dist_x;
        map_x += step_x;
        side = 0;
      } else {
        side_dist_y += delta_dist_y;
        map_y += step_y;
        side = 1;
      }

      if (map[map_x][map_y] == 1)
        hit = 1;
    }

    if (side == 0)
      perp_wall_dist = (map_x - player->x + (1 - step_x) / 2) / ray_dir_x;
    else
      perp_wall_dist = (map_y - player->y + (1 - step_y) / 2) / ray_dir_y;

    int height = (int)(HEIGHT / perp_wall_dist);
    draw_column(player, col, height, mlx_ptr, win_ptr);
  }
}

int main() {
  void *mlx_ptr;
  void *win_ptr;

  mlx_ptr = mlx_init();
  win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "Ray Casting");

  t_player player;
  player.x = 5.0;
  player.y = 5.0;
  player.dir_x = -1.0;
  player.dir_y = 0.0;
  player.plane_x = 0.0;
  player.plane_y = 0.66;

  mlx_loop_hook(mlx_ptr, render, &player);
  mlx_loop(mlx_ptr);

  return 0;
}
