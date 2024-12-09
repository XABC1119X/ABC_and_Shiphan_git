import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;
import javax.swing.*;

public class AnimatedGame {

    // 主角數值
    private int heroAttackPower = 3;
    private int heroHealth = 100;
    private int heroMaxHealth = 100;
    private int heroAttackSpeed = 3000; // 毫秒
    private int heroMana = 0;
    private final int heroMaxMana = 1000;
    private boolean isDefenseActive = false;

    // 怪物數值
    private int monsterAttackPower = 5;
    private int monsterHealth = 50;
    private int monsterUltimatePower = 20;
    private int monsterAttackSpeed = 5000; // 毫秒
    private int monsterUltimateInterval = 20000; // 毫秒

    // 遊戲視窗
    private JFrame frame;
    private JLabel heroLabel, monsterLabel, heroStatsLabel, monsterStatsLabel, manaLabel, ultimateWarningLabel;
    private JButton[] magicCards = new JButton[4];
    private Timer heroAttackTimer, monsterAttackTimer, manaRegenTimer, monsterUltimateTimer;

    // 人像圖案
    private ImageIcon heroPortrait, monsterPortrait,GGPortrait ,DEFPortrait ,AttackPortrait;

    public AnimatedGame() {
        showStartMenu();
    }

    // 顯示開始選單
    private void showStartMenu() {
        frame = new JFrame("Java 遊戲專案");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(800, 600);
        frame.setLayout(new BorderLayout());

        JLabel titleLabel = new JLabel("Welcome to the dungeon", SwingConstants.CENTER);
        titleLabel.setFont(new Font("Arial", Font.BOLD, 30));
        frame.add(titleLabel, BorderLayout.NORTH);

        JButton startButton = new JButton("Game Start");
        startButton.setFont(new Font("Arial", Font.BOLD, 20));
        startButton.addActionListener(e -> {
            frame.dispose();
            setupGameWindow();
            startTimers();
        });

        frame.add(startButton, BorderLayout.CENTER);
        frame.setVisible(true);
    }

    // 初始化遊戲視窗
    private void setupGameWindow() {
        frame = new JFrame("Java 遊戲專案");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(800, 600);
        frame.setLayout(null);

        // 載入人像
        heroPortrait = new ImageIcon("ABC_and_Shiphan_git\\Java 專案\\picture\\hero.png");
        monsterPortrait = new ImageIcon("ABC_and_Shiphan_git\\Java 專案\\picture\\monster.png"); 
        GGPortrait = new ImageIcon("ABC_and_Shiphan_git\\Java 專案\\picture\\GGgirl.png"); 
        DEFPortrait = new ImageIcon("ABC_and_Shiphan_git\\Java 專案\\picture\\DEF.png"); 
        AttackPortrait = new ImageIcon("ABC_and_Shiphan_git\\Java 專案\\picture\\attack.png"); 

        // 主角人像
        heroLabel = new JLabel(heroPortrait);
        heroLabel.setBounds(50, 130, 250, 250);

        // 怪物人像
        monsterLabel = new JLabel(monsterPortrait);
        monsterLabel.setBounds(450, 200, 250, 200);

        frame.add(heroLabel);
        frame.add(monsterLabel);

        // 數值顯示
        heroStatsLabel = new JLabel("主角 - 血量: " + heroHealth + "/" + heroMaxHealth + ", 攻擊力: " + heroAttackPower);
        heroStatsLabel.setBounds(10, 10, 300, 20);

        monsterStatsLabel = new JLabel("怪物 - 血量: " + monsterHealth + ", 攻擊力: " + monsterAttackPower);
        monsterStatsLabel.setBounds(500, 10, 300, 20);

        manaLabel = new JLabel("魔力值: " + heroMana + "/" + heroMaxMana);
        manaLabel.setBounds(10, 40, 300, 20);

        frame.add(heroStatsLabel);
        frame.add(monsterStatsLabel);
        frame.add(manaLabel);

        // 大招提示
        ultimateWarningLabel = new JLabel("", SwingConstants.CENTER);
        ultimateWarningLabel.setFont(new Font("Arial", Font.BOLD, 24));
        ultimateWarningLabel.setForeground(Color.RED);
        ultimateWarningLabel.setBounds(200, 100, 400, 50);
        frame.add(ultimateWarningLabel);

        // 魔法卡區域
        JPanel cardPanel = new JPanel();
        cardPanel.setLayout(new GridLayout(1, 4));
        cardPanel.setBounds(200, 500, 400, 50);

        for (int i = 0; i < 4; i++) {
            magicCards[i] = new JButton("魔法卡");
            magicCards[i].addActionListener(new MagicCardAction());
            cardPanel.add(magicCards[i]);
        }

        frame.add(cardPanel);
        frame.setVisible(true);
    }

    // 啟動各項定時器
    private void startTimers() {
        // 主角自動攻擊怪物
        heroAttackTimer = new Timer(heroAttackSpeed, e -> attackMonster());
        heroAttackTimer.start();

        // 怪物自動攻擊主角
        monsterAttackTimer = new Timer(monsterAttackSpeed, e -> attackHero());
        monsterAttackTimer.start();

        // 怪物大招攻擊
        monsterUltimateTimer = new Timer(monsterUltimateInterval, e -> monsterUltimateAttack());
        monsterUltimateTimer.start();

        // 魔力值恢復
        manaRegenTimer = new Timer(1000, e -> regenerateMana());
        manaRegenTimer.start();

        // 初始生成魔法卡
        generateMagicCards();
    }
    // move
    private void moveHero(int deltaX) {
        Point position = heroLabel.getLocation();
        heroLabel.setLocation(position.x + deltaX, position.y);
    }
    private void moveMonster(int deltaX) {
        Point position = monsterLabel.getLocation();
        monsterLabel.setLocation(position.x + deltaX, position.y);
    }

    // 主角攻擊怪物
    private void attackMonster() {
        if (monsterHealth > 0) {
            // 動畫效果：更換圖片與移動
            SwingUtilities.invokeLater(() -> {
                heroLabel.setIcon(AttackPortrait); // 更換為攻擊圖片
                moveHero(150); // 向前移動
            });
    
            // 短暫延遲後恢復圖片與位置
            Timer resetTimer = new Timer(500, e -> {
                heroLabel.setIcon(heroPortrait); // 恢復靜止圖片
                moveHero(-150); // 移回原位
                // 扣除怪物血量
                monsterHealth -= heroAttackPower;
                updateLabels();
                if (monsterHealth <= 0) {
                    gameEnd("主角勝利！");
                }
            });
            resetTimer.setRepeats(false);
            resetTimer.start();
        }
    }

    // 怪物攻擊主角
    private void attackHero() {
        if (isDefenseActive) {
            JOptionPane.showMessageDialog(frame, "防禦成功！主角免疫本次傷害！");
            isDefenseActive = false;
        } else if (heroHealth > 0) {
            moveMonster(-80); // 向前移動
            Timer resetTimer = new Timer(500, e -> {
                monsterLabel.setIcon(monsterPortrait); // 恢復靜止圖片
                moveMonster(80); // 移回原位
                // 扣除怪物血量
                heroHealth -= monsterAttackPower;
                updateLabels();
                if (heroHealth <= 0) {
                    gameEnd("怪物勝利！");
                }
            });
            resetTimer.setRepeats(false);
            resetTimer.start();
            
        }
    }

    // 怪物大招攻擊
    private void monsterUltimateAttack() {
        new Thread(() -> {
            for (int i = 3; i > 0; i--) {
                ultimateWarningLabel.setText("The monster ult attack: " + i + " sec");
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException ignored) {
                }
            }
            ultimateWarningLabel.setText("");
            if (heroHealth > 0) {
                heroHealth -= monsterUltimatePower;
                updateLabels();
                if (heroHealth <= 0) {
                    SwingUtilities.invokeLater(() -> {
                        heroLabel.setIcon(GGPortrait); 
                        moveHero(30); // 向前移動
                    });
                    gameEnd("怪物勝利！");
                }
            }
        }).start();
    }

    // 魔力值恢復
    private void regenerateMana() {
        if (heroMana < heroMaxMana) {
            heroMana++;
            manaLabel.setText("魔力值: " + heroMana + "/" + heroMaxMana);
        }
    }

    // 更新數值顯示
    private void updateLabels() {
        heroStatsLabel.setText("主角 - 血量: " + heroHealth + "/" + heroMaxHealth + ", 攻擊力: " + heroAttackPower);
        monsterStatsLabel.setText("怪物 - 血量: " + monsterHealth + ", 攻擊力: " + monsterAttackPower);
        manaLabel.setText("魔力值: " + heroMana + "/" + heroMaxMana);
    }

    // 遊戲結束
    private void gameEnd(String message) {
        JOptionPane.showMessageDialog(frame, message);
        System.exit(0);
    }

    // 隨機生成魔法卡
    private void generateMagicCards() {
        String[] cardNames = {"血量最大值 +5", "攻擊力 +1", "防禦", "血量 +20"};
        for (JButton button : magicCards) {
            String card = cardNames[new Random().nextInt(cardNames.length)];
            button.setText(card);
        }
    }

    // 魔法卡點擊事件
    private class MagicCardAction implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            JButton source = (JButton) e.getSource();
            String card = source.getText();

            if (heroMana >= 10) {
                heroMana -= 10;
                switch (card) {
                    case "血量最大值 +5":
                        heroMaxHealth += 5;
                        break;
                    case "攻擊力 +1":
                        heroAttackPower += 1;
                        break;
                    case "防禦":
                        isDefenseActive = true;
                        SwingUtilities.invokeLater(() -> {
                            heroLabel.setIcon(DEFPortrait); 
                            moveHero(30); // 向前移動
                        });
                        break;
                    case "血量 +20":
                        heroHealth = Math.min(heroMaxHealth, heroHealth + 20);
                        break;
                }
                generateMagicCards();
                updateLabels();
            } else {
                JOptionPane.showMessageDialog(frame, "魔力值不足！");
            }
        }
    }

    public static void main(String[] args) {
        new AnimatedGame();
    }
}
