import PrettyBT from './pbt'
import { Canvas, createCanvas } from 'canvas'
import fs from 'fs'
import path from 'path'

type Color = "RED" | "BLACK"

interface cppNode<T> {
  type: string,
  parent?: string,
  left?: string,
  right?: string,
  color: Color,
  value: T,
  id: string
}

interface btNode<T> {
  left?: string | btNode<T>,
  right?: string | btNode<T>,
  val: string,
  id: T,
  color: Color,
}

interface skipListJson {
  data: string[][],
  style: "SkipList"
}

interface bstJson<T> {
  data: cppNode<T>[]
  style: "BST" | "RedBlackBST"
}

interface disabledJson {
  style: "Disabled"
}


function nodeToStr<T>(tree: btNode<T>[], key?: string | btNode<T>) {
  console.log(tree);
  if (key && typeof (key) != "string") {
    key = key.val
  }
  const node = tree.find(elem => elem.val == key)
  if (!node) {
    return
  }
  let retVal: btNode<T> = { val: node.val, color: node.color, id: node.id }
  if (node.right) {
    retVal.right = nodeToStr(tree, node?.right)
  }
  if (node.left) {
    retVal.left = nodeToStr(tree, node?.left)
  }
  return retVal;
}

export function getDSA() {
  const { style }: skipListJson | bstJson<string | number> | disabledJson = JSON.parse(fs.readFileSync(path.join(__dirname, '../treeBuild.json'), { encoding: "utf-8" }))
  if (style == "BST") {
    return "Binary Tree Visualizer"
  } else if (style == "RedBlackBST") {
    return "Red Black Tree Visualizer"
  } else if (style == "SkipList") {
    return "Skip List Visualizer"
  } else if (style == "Disabled") {
    return "CS 375 Project Visualizer"
  }
}


function drawSkipList(canvas: Canvas, data: string[][]) {
  const masterLevel = data[0]
  const height = data.length
  const width = masterLevel.length

  if (masterLevel.length == 0) {
    return canvas
  }

  const arr = Array(height).fill(Array(width).fill(undefined))
  arr[0] = data[0];
  for (let i = 1; i < height; i++) {
    const level = Array(width).fill(undefined);
    for (const j of data[i]) {
      const index = masterLevel.indexOf(j)
      if (index >= 0) {
        level[index] = j
      }
    }
    arr[i] = level
  }

  const ctx = canvas.getContext("2d");
  const boxWidth = 140
  const boxHeight = 120
  const font = `${boxHeight / 3}px serif`
  const dividerWidth = 10
  const leftSide = boxWidth
  const rightSide = boxWidth
  const leftOffset = (canvas.width - arr[0].length * (boxWidth + dividerWidth) + rightSide) / 2
  const topOffset = (canvas.height - arr.length * boxHeight) / 2

  for (let i = 0; i < arr.length; i++) {
    ctx.beginPath()
    ctx.fillStyle = "#192227"
    ctx.arc(
      leftSide / 2 - dividerWidth + leftOffset - leftSide * .75,
      topOffset + (boxHeight * (arr.length - 1 - i)) + boxHeight / 2,
      leftSide / 2 - 3 * dividerWidth,
      0,
      2 * Math.PI
    )
    ctx.fill()
    ctx.textAlign = 'center'
    ctx.textBaseline = 'middle'
    ctx.font = `bold ${(leftSide / 2 - 3 * dividerWidth) / 2.5}px serif`
    ctx.fillStyle = "white"
    ctx.fillText(`Level ${i}`, leftSide / 2 - dividerWidth + leftOffset - leftSide * .75, topOffset + (boxHeight * (arr.length - 1 - i)) + boxHeight / 2)
    ctx.moveTo(leftSide / 2 - dividerWidth + leftOffset - leftSide * .75 + leftSide / 2 - 3 * dividerWidth, topOffset + (boxHeight * (arr.length - 1 - i)) + boxHeight / 2)
    ctx.lineTo(leftOffset, topOffset + (boxHeight * (arr.length - 1 - i)) + boxHeight / 2)
    ctx.stroke()
    ctx.fillStyle = "black"
  }

  for (let i = 0; i < arr[0].length; i++) {
    for (let j = 0; j < arr.length; j++) {
      if (arr[j][i]) {
        ctx.beginPath()
        ctx.rect(leftOffset + (boxWidth * i), topOffset + (boxHeight * (arr.length - 1 - j)), boxWidth - 10, boxHeight)
        ctx.textAlign = 'center'
        ctx.textBaseline = 'middle'
        ctx.font = font
        ctx.fillText(arr[j][i], leftOffset + (boxWidth * i) + boxWidth / 2 - dividerWidth / 2, topOffset + (boxHeight * (arr.length - 1 - j)) + boxHeight / 2)
        ctx.moveTo(leftOffset + (boxWidth * i) + boxWidth - dividerWidth, topOffset + (boxHeight * (arr.length - 1 - j)) + boxHeight / 2)
        ctx.lineTo(leftOffset + (boxWidth * i) + boxWidth, topOffset + (boxHeight * (arr.length - 1 - j)) + boxHeight / 2)
        ctx.stroke()
        ctx
      } else {
        ctx.beginPath()
        ctx.moveTo(leftOffset + (boxWidth * i), topOffset + (boxHeight * (arr.length - 1 - j)) + boxHeight / 2)
        ctx.lineTo(leftOffset + (boxWidth * i) + boxWidth, topOffset + (boxHeight * (arr.length - 1 - j)) + boxHeight / 2)
        ctx.stroke()
      }

    }

    for (let i = 0; i < arr.length; i++) {
      ctx.beginPath()
      ctx.fillStyle = "#cccccc"
      ctx.arc(
        leftOffset + (boxWidth * arr[0].length + 1) + rightSide / 2 - 3 * dividerWidth,
        topOffset + (boxHeight * (arr.length - 1 - i)) + boxHeight / 2,
        rightSide / 2 - 3 * dividerWidth,
        0,
        2 * Math.PI
      )
      ctx.fill();
      ctx.fillStyle = "black"
      ctx.textAlign = 'center'
      ctx.textBaseline = 'middle'
      ctx.font = `bold ${(rightSide / 2 - 3 * dividerWidth) / 2.5}px serif`
      ctx.fillText(`NIL`, leftOffset + (boxWidth * arr[0].length + 1) + rightSide / 2 - 3 * dividerWidth, topOffset + (boxHeight * (arr.length - 1 - i)) + boxHeight / 2)
      ctx.moveTo(leftSide / 2 - dividerWidth + leftOffset - leftSide * .75 + leftSide / 2 - 3 * dividerWidth, topOffset + (boxHeight * (arr.length - 1 - i)) + boxHeight / 2)
      ctx.lineTo(leftOffset, topOffset + (boxHeight * (arr.length - 1 - i)) + boxHeight / 2)
      ctx.stroke()
    }
  }
  return canvas
}

export function draw<T>() {
  const json: skipListJson | bstJson<T> | disabledJson = JSON.parse(fs.readFileSync(path.join(__dirname, '../treeBuild.json'), { encoding: "utf-8" }))
  const canvas = createCanvas(1800, 800)
  if (json.style == "Disabled") {
    return canvas
  } else if (json.style == "SkipList") {
    drawSkipList(canvas, json.data as string[][]);
  } else {
    const { data, style } = json as bstJson<T>
    const root = data.find(node => !node.parent)
    const renamed: btNode<T>[] = data.map((node) => {
      return {
        left: node.left,
        right: node.right,
        val: node.id,
        id: node.value,
        color: style == "RedBlackBST" ? node.color : "BLACK"
      }
    })

    let tree = nodeToStr(renamed, root?.id)
    console.log(tree);
    PrettyBT.drawBinaryTree(canvas, { ...tree }, 30);
  }
  return canvas;
}