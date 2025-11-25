#!/bin/bash

# 检查是否提供了提交信息
if [ -z "$1" ]; then
    echo "错误：请提供提交信息。"
    echo "用法: ./script_name.sh \"您的提交信息\""
    exit 1
fi

# 检查当前目录是否为git仓库
if ! git rev-parse --git-dir > /dev/null 2>&1; then
    echo "错误：当前目录不是一个Git仓库。"
    exit 1
fi

# 添加更改到暂存区
git add .

# 提交更改
git commit -m "$1"

# 检查提交是否成功
if [ $? -eq 0 ]; then
    echo "提交成功，开始推送所有分支到远程仓库 'stm32-new'..."

    # 推送所有分支到指定的远程仓库
    git push stm32-new --all
    if [ $? -eq 0 ]; then
        echo "所有分支已成功推送到 stm32-new: $1"
    else
        echo "推送失败，请检查网络连接或分支冲突: $1"
        exit 1
    fi
else
    echo "提交失败，请检查提交信息或文件状态: $1"
    exit 1
fi
