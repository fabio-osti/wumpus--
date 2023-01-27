bool seeded = false;
void unique_seed()
{
	if (seeded)
		return;
	srand(time(NULL));
	seeded = true;
}
