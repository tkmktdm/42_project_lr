def ft_count_harvest_recursive() -> None:
    def count_day(day: int, days: int) -> None:
        if day > days:
            return
        print(f"Day {day}")
        count_day(day + 1, days)

    days = int(input("Days until harvest: "))
    count_day(1, days)
    print("Harvest time!")
