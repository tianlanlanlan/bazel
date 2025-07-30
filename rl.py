# 导入需要使用的库,其中numpy是支持数组和矩阵运算的科学计算库,而matplotlib是绘图库
import numpy as np
import matplotlib.pyplot as plt


class BernoulliBandit:
    """伯努利多臂老虎机,输入K表示拉杆个数"""

    def __init__(self, K):
        self.probs = np.random.uniform(
            size=K
        )  # 随机生成K个0～1的数,作为拉动每根拉杆的获奖
        # 概率
        self.best_idx = np.argmax(self.probs)  # 获奖概率最大的拉杆
        self.best_prob = self.probs[self.best_idx]  # 最大的获奖概率
        self.K = K

    def step(self, k):
        # 当玩家选择了k号拉杆后,根据拉动该老虎机的k号拉杆获得奖励的概率返回1（获奖）或0（未
        # 获奖）
        if np.random.rand() < self.probs[k]:
            return 1
        else:
            return 0


class Solver:
    """多臂老虎机算法基本框架"""

    def __init__(self, bandit):
        self.bandit = bandit
        self.counts = np.zeros(self.bandit.K)  # 每根拉杆的尝试次数
        self.regret = 0.0  # 当前步的累积懊悔
        self.actions = []  # 维护一个列表,记录每一步的动作
        self.regrets = []  # 维护一个列表,记录每一步的累积懊悔

    def update_regret(self, k):
        # 计算累积懊悔并保存,k为本次动作选择的拉杆的编号
        self.regret += self.bandit.best_prob - self.bandit.probs[k]
        self.regrets.append(self.regret)

    def run_one_step(self):
        # 返回当前动作选择哪一根拉杆,由每个具体的策略实现
        raise NotImplementedError

    def run(self, num_steps):
        # 运行一定次数,num_steps为总运行次数
        for _ in range(num_steps):
            k = self.run_one_step()
            self.counts[k] += 1
            self.actions.append(k)
            self.update_regret(k)


class EpsilonGreedySolver(Solver):
    """ε-贪婪算法"""

    def __init__(self, bandit, epsilon=0.01, init_prob=1.0):
        super().__init__(bandit)
        self.epsilon = epsilon
        self.estimates = np.array([init_prob] * bandit.K)  # 每根拉杆的获奖概率估计值
        print(
            f"使用ε-贪婪算法,探索率为{self.epsilon:.2f}, 初始估计值为{init_prob:.2f}, 每根拉杆的获奖概率估计值为{self.estimates}"
        )

    def run_one_step(self):
        # 以ε的概率随机选择一根拉杆,否则选择当前获奖概率最大的拉杆
        random_prob = np.random.rand()
        print(f"random_prob = {random_prob:.4f}")
        if random_prob < self.epsilon:
            k = np.random.randint(0, self.bandit.K)
        else:
            k = np.argmax(self.estimates)
        r = self.bandit.step(k)  # 拉动k号拉杆获得奖励
        self.estimates[k] += (
            1.0 / (self.counts[k] + 1) * (r - self.estimates[k])
        )  # 更新k号拉杆的获奖概率估计值
        return k


def plot_results(solvers, solver_names):
    """生成累积懊悔随时间变化的图像。输入solvers是一个列表,列表中的每个元素是一种特定的策略。
    而solver_names也是一个列表,存储每个策略的名称"""
    for idx, solver in enumerate(solvers):
        time_list = range(len(solver.regrets))
        plt.plot(time_list, solver.regrets, label=solver_names[idx])
    plt.xlabel("Time steps")
    plt.ylabel("Cumulative regrets")
    plt.title("%d-armed bandit" % solvers[0].bandit.K)
    plt.legend()
    plt.savefig("epsilon_greedy_results.png")


np.random.seed(1)  # 设定随机种子,使实验具有可重复性
K = 10
bandit_10_arm = BernoulliBandit(K)
print("随机生成了一个%d臂伯努利老虎机" % K)
print(
    "获奖概率最大的拉杆为%d号,其获奖概率为%.4f"
    % (bandit_10_arm.best_idx, bandit_10_arm.best_prob)
)


np.random.seed(1)
epsilon_greedy_solver = EpsilonGreedySolver(bandit_10_arm, epsilon=0.01)
epsilon_greedy_solver.run(5000)
print("epsilon-贪婪算法的累积懊悔为：", epsilon_greedy_solver.regret)
plot_results([epsilon_greedy_solver], ["EpsilonGreedy"])
