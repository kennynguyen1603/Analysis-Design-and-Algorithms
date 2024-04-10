from ortools.linear_solver import pywraplp

#"CBC" (một solver dành cho bài toán nguyên lập trình tuyến tính).
#"GLOP" (dành cho bài toán lập trình tuyến tính).

def knapsack_problem(values, weight, max_weight):
    solver = pywraplp.Solver.CreateSolver("CBC")
    if not solver:
        return

    number_items = len(values)

    # Biến quyết định
    x = [solver.IntVar(0, 1, f'x[{i}]') for i in range(number_items)]

    # Đièu kiện ràng buộc
    weight_constraint = solver.Sum(x[i] * weight[i] for i in range(number_items))
    solver.Add(weight_constraint <= max_weight)

    # Hàm mục tiêu
    objective = solver.Objective()
    for i in range(number_items):
        objective.SetCoefficient(x[i], values[i])
    objective.SetMaximization()

    # Gọi solver
    status = solver.Solve()

    if status == pywraplp.Solver.OPTIMAL:
        print("Giải pháp tối ưu:")
        # total_weight = sum(x[i].solution_value() * weight[i] for i in range(number_items))
        total_weight = sum(x[i].solution_value() * weight[i] for i in range(number_items))
        total_value = sum(x[i].solution_value() * values[i] for i in range(number_items))
        print(f"Tổng giá trị: {total_value}")
        print(f"Tổng trọng lượng: {total_weight}")
        print("Các đồ vật được chọn:")
        for i in range(number_items):
            if x[i].solution_value() > 0:
                print(f"Đồ vật {i} - Trọng lượng: {weight[i]}, Giá trị: {values[i]}")
    else:
        print("Không tìm thấy giải pháp tối ưu.")

values = [30, 25, 2, 6]
weight = [15, 10, 2, 4]
max_weight = 27
knapsack_problem(values, weight, max_weight)
