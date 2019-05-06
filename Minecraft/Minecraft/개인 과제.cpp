#define _CRT_SECURE_NO_WARNINGS
#include <CoalaMOD.h>
#pragma comment(lib, "CoalaMOD.lib")

int main()
{

	BlockID stone_brick = createBricks(BRICKS_STONE);
	BlockID spruce_plank = createPlanks(PLANKS_SPRUCE);
	WoolID white_wool = createWool(COLOR_WHITE);
	PaneID glasspane = createPane(PANE_GLASS);

	WoodID spruce = createWood(WOOD_SPRUCE, STRIP_UP_DOWN);
	WoodID spruceNS = createWood(WOOD_SPRUCE, STRIP_NORTH_SOUTH);
	WoodID spruceEW = createWood(WOOD_SPRUCE, STRIP_EAST_WEST);

	StairsID stone_stair = createStairs(STAIRS_STONE_BRICK);
	StairsID stone_stair2 = createStairs(STAIRS_STONE_BRICK, true);
	StairsID spruce_stair = createStairs(STAIRS_SPRUCE, true);

	FenceID spruce_fence = createFence(FENCE_SPRUCE);
	FenceID nether_fence = createFence(FENCE_NETHER_BRICK);



	int sx, sy, sz, ex, ey, ez;

	// 최소 크기 16 x 16, 높이 40정도 권장
	printf("sx, sy, sz의 값을 입력하시오: ");
	scanf("%d %d %d", &sx, &sy, &sz);
	printf("ex, ey, ez의 값을 입력하시오: ");
	scanf("%d %d %d", &ex, &ey, &ez);

	int fx, fy, fz, lx, ly, lz;

	// 입력받은 두개의 값들 중 작은 값을 첫번째 위치로, 큰 값을 마지막 위치로 설정
	if (sx < ex) fx = sx, lx = ex;
	else fx = ex, lx = sx;

	if (sy < ey) fy = sy, ly = ey;
	else fy = ey, ly = sy;

	if (sz < ez) fz = sz, lz = ez;
	else fz = ez, lz = sz;

	int xlen = abs(lx - fx), ylen = abs(ly - fy), zlen = abs(lz - fz); //각 좌표의 길이 구하기

	int floor = 0, currentY = 0; // 층의 수와 현재 y좌표의 위치


	// 바닥 짓는 과정
	for (int x = fx + 2; x <= lx - 2; x++) // x 좌표
	{
		if (x == fx + 2 || x == lx - 2) // 바닥의 끝 부분
		{
			locateWood(spruceNS, x, fy, fz + 1);
			locateWood(spruceNS, x, fy, lz - 1);
			locateWood(spruce, x, fy, fz + 2);
			locateWood(spruce, x, fy, lz - 2);
		}

		else if (x == fx + (xlen / 2)) // 바닥의 중간 지점
		{
			if (xlen % 2 == 1) // 중간이 2개일 때
			{
				locateWood(spruceNS, x, fy, fz + 1);
				locateWood(spruceNS, x, fy, lz - 1);
				locateWood(spruce, x, fy, fz + 2);
				locateWood(spruce, x, fy, lz - 2);
				locateWood(spruceNS, x + 1, fy, fz + 1);
				locateWood(spruceNS, x + 1, fy, lz - 1);
				locateWood(spruce, x + 1, fy, fz + 2);
				locateWood(spruce, x + 1, fy, lz - 2);
				x++; // 중간 건너뛰기
			}

			else // 중간이 1개일 때
			{
				locateWood(spruceNS, x, fy, fz + 1);
				locateWood(spruceNS, x, fy, lz - 1);
				locateWood(spruce, x, fy, fz + 2);
				locateWood(spruce, x, fy, lz - 2);
			}

		}

		else // 바닥의 나머지 부분
		{
			installStairs(stone_stair, x, fy, fz + 1, FACING_SOUTH);
			installStairs(stone_stair, x, fy, lz - 1, FACING_NORTH);
			locateBlock(stone_brick, x, fy, fz + 2);
			locateBlock(stone_brick, x, fy, lz - 2);
		}

	}

	for (int z = fz + 2; z <= lz - 2; z++) // z 좌표
	{
		if (z == fz + 2 || z == lz - 2) // 바닥의 끝 부분
		{
			locateWood(spruceEW, fx + 1, fy, z);
			locateWood(spruceEW, lx - 1, fy, z);
			locateWood(spruce, fx + 2, fy, z);
			locateWood(spruce, lx - 2, fy, z);
		}

		else if (z == fz + (zlen / 2)) // 바닥의 중간 지점
		{
			if (zlen % 2 == 1) // 중간이 2개일 때
			{
				locateWood(spruceNS, fx + 1, fy, z);
				locateWood(spruceNS, lx - 1, fy, z);
				locateWood(spruce, fx + 2, fy, z);
				locateWood(spruce, lx - 2, fy, z);
				locateWood(spruceNS, fx + 1, fy, z + 1);
				locateWood(spruceNS, lx - 1, fy, z + 1);
				locateWood(spruce, fx + 2, fy, z + 1);
				locateWood(spruce, lx - 2, fy, z + 1);
				z++;
			}

			else // 중간이 1개일 때
			{
				locateWood(spruceEW, fx + 1, fy, z);
				locateWood(spruceEW, lx - 1, fy, z);
				locateWood(spruce, fx + 2, fy, z);
				locateWood(spruce, lx - 2, fy, z);
			}

		}

		else // 바닥의 나머지 부분
		{
			installStairs(stone_stair, fx + 1, fy, z, FACING_EAST);
			installStairs(stone_stair, lx - 1, fy, z, FACING_WEST);
			locateBlock(stone_brick, fx + 2, fy, z);
			locateBlock(stone_brick, lx - 2, fy, z);
		}


	}

	/*지정받은 높이대로 일정한 수의 층을 짓도록 한다.
	건물의 높이가 최대 높이를 넘어가지 않도록 조정하며, 층 수를 기록하여 지붕을 지을 y 좌표 값을 정한다.*/
	for (int y = fy + 1; y <= ly - 6; y = y + 6)
	{

		for (int x = fx + 2; x <= lx - 2; x++)
		{
			if (x == fx + 2 || x == lx - 2)
			{
				for (int h = 0; h < 6; h++)
				{
					locateWood(spruce, x, y + h, fz + 2);
					locateWood(spruce, x, y + h, lz - 2);
				}

				installStairs(stone_stair, x, y, fz + 1, FACING_SOUTH);
				installStairs(stone_stair, x, y, lz - 1, FACING_NORTH);
				locateFence(nether_fence, x, y + 1, fz + 1);
				locateFence(nether_fence, x, y + 1, lz - 1);
				locateFence(spruce_fence, x, y + 2, fz + 1);
				locateFence(spruce_fence, x, y + 2, lz - 1);
				locateFence(nether_fence, x, y + 3, fz + 1);
				locateFence(nether_fence, x, y + 3, lz - 1);
				installStairs(stone_stair2, x, y + 4, fz + 1, FACING_SOUTH);
				installStairs(stone_stair2, x, y + 4, lz - 1, FACING_NORTH);
				locateWood(spruceNS, x, y + 5, fz + 1);
				locateWood(spruceNS, x, y + 5, lz - 1);

				installStairs(stone_stair, fx + 3, y, fz + 2, FACING_WEST);
				installStairs(stone_stair2, fx + 3, y + 4, fz + 2, FACING_WEST);
				installStairs(stone_stair, lx - 3, y, fz + 2, FACING_EAST);
				installStairs(stone_stair2, lx - 3, y + 4, fz + 2, FACING_EAST);
				installStairs(stone_stair, fx + 3, y, lz - 2, FACING_WEST);
				installStairs(stone_stair2, fx + 3, y + 4, lz - 2, FACING_WEST);
				installStairs(stone_stair, lx - 3, y, lz - 2, FACING_EAST);
				installStairs(stone_stair2, lx - 3, y + 4, lz - 2, FACING_EAST);
			}

			else if (x == fx + (xlen / 2))
			{
				if (xlen % 2 == 1)
				{
					for (int h = 0; h < 6; h++)
					{
						locateWood(spruce, x, y + h, fz + 2);
						locateWood(spruce, x, y + h, lz - 2);
						locateWood(spruce, x + 1, y + h, fz + 2);
						locateWood(spruce, x + 1, y + h, lz - 2);
					}

					for (int a = 0; a < 2; a++)
					{
						installStairs(stone_stair, x + a, y, fz + 1, FACING_SOUTH);
						installStairs(stone_stair, x + a, y, lz - 1, FACING_NORTH);
						locateFence(nether_fence, x + a, y + 1, fz + 1);
						locateFence(nether_fence, x + a, y + 1, lz - 1);
						locateFence(spruce_fence, x + a, y + 2, fz + 1);
						locateFence(spruce_fence, x + a, y + 2, lz - 1);
						locateFence(nether_fence, x + a, y + 3, fz + 1);
						locateFence(nether_fence, x + a, y + 3, lz - 1);
						installStairs(stone_stair2, x + a, y + 4, fz + 1, FACING_SOUTH);
						installStairs(stone_stair2, x + a, y + 4, lz - 1, FACING_NORTH);
						locateWood(spruceNS, x + a, y + 5, fz + 1);
						locateWood(spruceNS, x + a, y + 5, lz - 1);

						installStairs(stone_stair, x - 1, y, fz + 2, FACING_EAST);
						installStairs(stone_stair2, x - 1, y + 4, fz + 2, FACING_EAST);
						installStairs(stone_stair, x + 2, y, fz + 2, FACING_WEST);
						installStairs(stone_stair2, x + 2, y + 4, fz + 2, FACING_WEST);
						installStairs(stone_stair, x - 1, y, lz - 2, FACING_EAST);
						installStairs(stone_stair2, x - 1, y + 4, lz - 2, FACING_EAST);
						installStairs(stone_stair, x + 2, y, lz - 2, FACING_WEST);
						installStairs(stone_stair2, x + 2, y + 4, lz - 2, FACING_WEST);
					}
					x++;
				}
				else
				{
					for (int h = 0; h < 6; h++)
					{
						locateWood(spruce, x, y + h, fz + 2);
						locateWood(spruce, x, y + h, lz - 2);
					}

					installStairs(stone_stair, x, y, fz + 1, FACING_SOUTH);
					installStairs(stone_stair, x, y, lz - 1, FACING_NORTH);
					locateFence(nether_fence, x, y + 1, fz + 1);
					locateFence(nether_fence, x, y + 1, lz - 1);
					locateFence(spruce_fence, x, y + 2, fz + 1);
					locateFence(spruce_fence, x, y + 2, lz - 1);
					locateFence(nether_fence, x, y + 3, fz + 1);
					locateFence(nether_fence, x, y + 3, lz - 1);
					installStairs(stone_stair2, x, y + 4, fz + 1, FACING_SOUTH);
					installStairs(stone_stair2, x, y + 4, lz - 1, FACING_NORTH);
					locateWood(spruceNS, x, y + 5, fz + 1);
					locateWood(spruceNS, x, y + 5, lz - 1);

					installStairs(stone_stair, x - 1, y, fz + 2, FACING_EAST);
					installStairs(stone_stair2, x - 1, y + 4, fz + 2, FACING_EAST);
					installStairs(stone_stair, x + 1, y, fz + 2, FACING_WEST);
					installStairs(stone_stair2, x + 1, y + 4, fz + 2, FACING_WEST);
					installStairs(stone_stair, x - 1, y, lz - 2, FACING_EAST);
					installStairs(stone_stair2, x - 1, y + 4, lz - 2, FACING_EAST);
					installStairs(stone_stair, x + 1, y, lz - 2, FACING_WEST);
					installStairs(stone_stair2, x + 1, y + 4, lz - 2, FACING_WEST);
				}

			}

			else
			{
				for (int h = 0; h < 5; h++)
				{
					locateWool(white_wool, x, y + h, fz + 3);
					locateWool(white_wool, x, y + h, lz - 3);
					locateBlock(stone_brick, x, y + 5, fz + 2);
					locateBlock(stone_brick, x, y + 5, lz - 2);
				}

				if ((x >= fx + 4 && x < fx + (xlen / 2) - 1) || (x > lx - (xlen / 2) + 1 && x <= lx - 4))
				{
					for (int h = 1; h < 4; h++)
					{
						locatePane(glasspane, x, y + h, fz + 3);
						locatePane(glasspane, x, y + h, lz - 3);
					}
				}
			}

		}

		for (int z = fz + 2; z <= lz - 2; z++)
		{
			if (z == fz + 2 || z == lz - 2)
			{
				for (int h = 0; h < 6; h++)
				{
					locateWood(spruce, fx + 2, y + h, z);
					locateWood(spruce, lx - 2, y + h, z);
				}

				installStairs(stone_stair, fx + 1, y, z, FACING_EAST);
				installStairs(stone_stair, lx - 1, y, z, FACING_WEST);
				locateFence(nether_fence, fx + 1, y + 1, z);
				locateFence(nether_fence, lx - 1, y + 1, z);
				locateFence(spruce_fence, fx + 1, y + 2, z);
				locateFence(spruce_fence, lx - 1, y + 2, z);
				locateFence(nether_fence, fx + 1, y + 3, z);
				locateFence(nether_fence, lx - 1, y + 3, z);
				installStairs(stone_stair2, fx + 1, y + 4, z, FACING_EAST);
				installStairs(stone_stair2, lx - 1, y + 4, z, FACING_WEST);
				locateWood(spruceEW, fx + 1, y + 5, z);
				locateWood(spruceEW, lx - 1, y + 5, z);

				installStairs(stone_stair, fx + 2, y, fz + 3, FACING_NORTH);
				installStairs(stone_stair2, fx + 2, y + 4, fz + 3, FACING_NORTH);
				installStairs(stone_stair, lx - 2, y, fz + 3, FACING_NORTH);
				installStairs(stone_stair2, lx - 2, y + 4, fz + 3, FACING_NORTH);
				installStairs(stone_stair, fx + 2, y, lz - 3, FACING_SOUTH);
				installStairs(stone_stair2, fx + 2, y + 4, lz - 3, FACING_SOUTH);
				installStairs(stone_stair, lx - 2, y, lz - 3, FACING_SOUTH);
				installStairs(stone_stair2, lx - 2, y + 4, lz - 3, FACING_SOUTH);
			}

			else if (z == fz + (zlen / 2))
			{
				if (zlen % 2 == 1)
				{
					for (int h = 0; h < 6; h++)
					{
						locateWood(spruce, fx + 2, y + h, fz + 2);
						locateWood(spruce, lx - 2, y + h, lz - 2);
						locateWood(spruce, fx + 2, y + h, z + 1);
						locateWood(spruce, lx - 2, y + h, z + 1);
					}

					for (int a = 0; a < 2; a++)
					{
						installStairs(stone_stair, fx + 1, y, z + a, FACING_EAST);
						installStairs(stone_stair, lx - 1, y, z + a, FACING_WEST);
						locateFence(nether_fence, fx + 1, y + 1, z + a);
						locateFence(nether_fence, lx - 1, y + 1, z + a);
						locateFence(spruce_fence, fx + 1, y + 2, z + a);
						locateFence(spruce_fence, lx - 1, y + 2, z + a);
						locateFence(nether_fence, fx + 1, y + 3, z + a);
						locateFence(nether_fence, lx - 1, y + 3, z + a);
						installStairs(stone_stair2, fx + 1, y + 4, z + a, FACING_EAST);
						installStairs(stone_stair2, lx - 1, y + 4, z + a, FACING_WEST);
						locateWood(spruceEW, fx + 1, y + 5, z + a);
						locateWood(spruceEW, lx - 1, y + 5, z + a);

						installStairs(stone_stair, fx + 2, y, z - 1, FACING_SOUTH);
						installStairs(stone_stair2, fx + 2, y + 4, z - 1, FACING_SOUTH);
						installStairs(stone_stair, fx + 2, y, z + 2, FACING_NORTH);
						installStairs(stone_stair2, fx + 2, y + 4, z + 2, FACING_NORTH);
						installStairs(stone_stair, lx - 2, y, z - 1, FACING_SOUTH);
						installStairs(stone_stair2, lx - 2, y + 4, z - 1, FACING_SOUTH);
						installStairs(stone_stair, lx - 2, y, z + 2, FACING_NORTH);
						installStairs(stone_stair2, lx - 2, y + 4, z + 2, FACING_NORTH);
					}
					z++;
				}
				else
				{
					for (int h = 0; h < 6; h++)
					{
						locateWood(spruce, fx + 2, y + h, z);
						locateWood(spruce, lx - 2, y + h, z);
					}

					installStairs(stone_stair, fx + 1, y, z, FACING_EAST);
					installStairs(stone_stair, lx - 1, y, z, FACING_WEST);
					locateFence(nether_fence, fx + 1, y + 1, z);
					locateFence(nether_fence, lx - 1, y + 1, z);
					locateFence(spruce_fence, fx + 1, y + 2, z);
					locateFence(spruce_fence, lx - 1, y + 2, z);
					locateFence(nether_fence, fx + 1, y + 3, z);
					locateFence(nether_fence, lx - 1, y + 3, z);
					installStairs(stone_stair2, fx + 1, y + 4, z, FACING_EAST);
					installStairs(stone_stair2, lx - 1, y + 4, z, FACING_WEST);
					locateWood(spruceEW, fx + 1, y + 5, z);
					locateWood(spruceEW, lx - 1, y + 5, z);

					installStairs(stone_stair, fx + 2, y, z - 1, FACING_SOUTH);
					installStairs(stone_stair2, fx + 2, y + 4, z - 1, FACING_SOUTH);
					installStairs(stone_stair, fx + 2, y, z + 1, FACING_NORTH);
					installStairs(stone_stair2, fx + 2, y + 4, z + 1, FACING_NORTH);
					installStairs(stone_stair, lx - 2, y, z - 1, FACING_SOUTH);
					installStairs(stone_stair2, lx - 2, y + 4, z - 1, FACING_SOUTH);
					installStairs(stone_stair, lx - 2, y, z + 1, FACING_NORTH);
					installStairs(stone_stair2, lx - 2, y + 4, z + 1, FACING_NORTH);
				}

			}

			else
			{
				for (int h = 0; h < 5; h++)
				{
					locateWool(white_wool, fx + 3, y + h, z);
					locateWool(white_wool, lx - 3, y + h, z);
					locateBlock(stone_brick, fx + 2, y + 5, z);
					locateBlock(stone_brick, lx - 2, y + 5, z);
				}

				if ((z >= fz + 4 && z < fz + (zlen / 2) - 1) || (z > lz - (zlen / 2) + 1 && z <= lz - 4))
				{
					for (int h = 1; h < 4; h++)
					{
						locatePane(glasspane, fx + 3, y + h, z);
						locatePane(glasspane, lx - 3, y + h, z);
					}
				}

			}

		}

		floor++; // 층의 수 구하기

	}
	currentY = fy + (6 * floor); // 지붕을 지을 y 좌표

	//지붕 짓기

	for (int x = fx + 2; x <= lx - 2; x++)
	{
		for (int z = fz + 2; z <= lz - 2; z++)
		{
			locateBlock(stone_brick, x, currentY, z);
		}
	}

	// 중간값 지점에서 지붕이 겹쳐지는 것을 방지하기 위해 시작점과 끝점에서부터 중간지점을 향하며 지붕을 짓는다.

	for (int x = 1; x < xlen / 2; x++) // x 좌표 지붕
	{
		if (x % 3 == 2)
		{
			locateBlock(stone_brick, fx + x, currentY, fz + 1);
			locateBlock(stone_brick, lx - x, currentY, fz + 1);
			locateBlock(stone_brick, fx + x, currentY, lz - 1);
			locateBlock(stone_brick, lx - x, currentY, lz - 1); // 석재 블록
			installStairs(spruce_stair, fx + x, currentY, fz, FACING_SOUTH);
			installStairs(spruce_stair, lx - x, currentY, fz, FACING_SOUTH);
			installStairs(spruce_stair, fx + x, currentY, lz, FACING_NORTH);
			installStairs(spruce_stair, lx - x, currentY, lz, FACING_NORTH); // 나무 계단
			locatePlanks(spruce_plank, fx + x, currentY + 1, fz);
			locatePlanks(spruce_plank, lx - x, currentY + 1, fz);
			locatePlanks(spruce_plank, fx + x, currentY + 1, lz);
			locatePlanks(spruce_plank, lx - x, currentY + 1, lz); // 나무 판자
		}

		else
		{
			installStairs(spruce_stair, fx + x, currentY, fz + 1, FACING_SOUTH);
			installStairs(spruce_stair, lx - x, currentY, fz + 1, FACING_SOUTH);
			installStairs(spruce_stair, fx + x, currentY, lz - 1, FACING_NORTH);
			installStairs(spruce_stair, lx - x, currentY, lz - 1, FACING_NORTH); // 나무 계단
			locatePlanks(spruce_plank, fx + x, currentY + 1, fz + 1);
			locatePlanks(spruce_plank, lx - x, currentY + 1, fz + 1);
			locatePlanks(spruce_plank, fx + x, currentY + 1, lz - 1);
			locatePlanks(spruce_plank, lx - x, currentY + 1, lz - 1); // 나무 판자
		}
	}

	for (int z = 1; z < zlen / 2; z++) // z 좌표 지붕
	{
		if (z % 3 == 2)
		{
			locateBlock(stone_brick, fx + 1, currentY, fz + z);
			locateBlock(stone_brick, fx + 1, currentY, lz - z);
			locateBlock(stone_brick, lx - 1, currentY, fz + z);
			locateBlock(stone_brick, lx - 1, currentY, lz - z); // 석재 블록
			installStairs(spruce_stair, fx, currentY, fz + z, FACING_EAST);
			installStairs(spruce_stair, fx, currentY, lz - z, FACING_EAST);
			installStairs(spruce_stair, lx, currentY, fz + z, FACING_WEST);
			installStairs(spruce_stair, lx, currentY, lz - z, FACING_WEST); // 나무 계단
			locatePlanks(spruce_plank, fx, currentY + 1, fz + z);
			locatePlanks(spruce_plank, fx, currentY + 1, lz - z);
			locatePlanks(spruce_plank, lx, currentY + 1, fz + z);
			locatePlanks(spruce_plank, lx, currentY + 1, lz - z); // 나무 판자
		}

		else
		{
			installStairs(spruce_stair, fx + 1, currentY, fz + z, FACING_EAST);
			installStairs(spruce_stair, fx + 1, currentY, lz - z, FACING_EAST);
			installStairs(spruce_stair, lx - 1, currentY, fz + z, FACING_WEST);
			installStairs(spruce_stair, lx - 1, currentY, lz - z, FACING_WEST); // 나무 계단
			locatePlanks(spruce_plank, fx + 1, currentY + 1, fz + z);
			locatePlanks(spruce_plank, fx + 1, currentY + 1, lz - z);
			locatePlanks(spruce_plank, lx - 1, currentY + 1, fz + z);
			locatePlanks(spruce_plank, lx - 1, currentY + 1, lz - z); // 나무 판자
		}

	}

	// x 좌표 지붕 중간지점

	if (xlen % 2 == 1) // 중간지점이 2개일 경우
	{
		installStairs(spruce_stair, fx + (xlen / 2), currentY, fz, FACING_SOUTH);
		installStairs(spruce_stair, fx + (xlen / 2) + 1, currentY, fz, FACING_SOUTH);
		installStairs(spruce_stair, fx + (xlen / 2), currentY, lz, FACING_NORTH);
		installStairs(spruce_stair, fx + (xlen / 2) + 1, currentY, lz, FACING_NORTH);
		locatePlanks(spruce_plank, fx + (xlen / 2), currentY + 1, fz);
		locatePlanks(spruce_plank, fx + (xlen / 2) + 1, currentY + 1, fz);
		locatePlanks(spruce_plank, fx + (xlen / 2), currentY + 1, lz);
		locatePlanks(spruce_plank, fx + (xlen / 2) + 1, currentY + 1, lz);
	}

	else // 중간지점이 1개일 경우
	{
		installStairs(spruce_stair, fx + (xlen / 2), currentY, fz, FACING_SOUTH);
		installStairs(spruce_stair, fx + (xlen / 2), currentY, lz, FACING_NORTH);
		locatePlanks(spruce_plank, fx + (xlen / 2), currentY + 1, fz);
		locatePlanks(spruce_plank, fx + (xlen / 2), currentY + 1, lz);
	}

	// z 좌표 지붕 중간지점

	if (zlen % 2 == 1) // 중간지점이 2개일 경우
	{
		installStairs(spruce_stair, fx, currentY, fz + (zlen / 2), FACING_EAST);
		installStairs(spruce_stair, fx, currentY, fz + (zlen / 2) + 1, FACING_EAST);
		installStairs(spruce_stair, lx, currentY, fz + (zlen / 2), FACING_WEST);
		installStairs(spruce_stair, lx, currentY, fz + (zlen / 2) + 1, FACING_WEST);
		locatePlanks(spruce_plank, fx, currentY + 1, fz + (zlen / 2));
		locatePlanks(spruce_plank, fx, currentY + 1, fz + (zlen / 2) + 1);
		locatePlanks(spruce_plank, lx, currentY + 1, fz + (zlen / 2));
		locatePlanks(spruce_plank, lx, currentY + 1, fz + (zlen / 2) + 1);
	}

	else // 중간지점이 1개일 경우
	{
		installStairs(spruce_stair, fx, currentY, fz + (zlen / 2), FACING_EAST);
		installStairs(spruce_stair, lx, currentY, fz + (zlen / 2), FACING_WEST);
		locatePlanks(spruce_plank, fx, currentY + 1, fz + (zlen / 2));
		locatePlanks(spruce_plank, lx, currentY + 1, fz + (zlen / 2));
	}

}