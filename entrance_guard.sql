/*
 Navicat Premium Data Transfer

 Source Server         : MYSQL
 Source Server Type    : MySQL
 Source Server Version : 80020
 Source Host           : localhost:3306
 Source Schema         : entrance_guard

 Target Server Type    : MySQL
 Target Server Version : 80020
 File Encoding         : 65001

 Date: 03/12/2020 12:24:06
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for allrecord
-- ----------------------------
DROP TABLE IF EXISTS `allrecord`;
CREATE TABLE `allrecord`  (
  `all_num` int(0) NOT NULL AUTO_INCREMENT,
  `all_card_id` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `all_out_time` time(0) NULL DEFAULT NULL,
  `all_in_time` time(0) NULL DEFAULT NULL,
  `all_howlong` time(0) NULL DEFAULT NULL,
  `all_temperature` int(0) NULL DEFAULT NULL,
  PRIMARY KEY (`all_num`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 88 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of allrecord
-- ----------------------------
INSERT INTO `allrecord` VALUES (124, 'F0398D43', '00:03:44', NULL, NULL, 22);
INSERT INTO `allrecord` VALUES (125, 'F0398D43', NULL, '00:03:49', '00:00:05', 22);
INSERT INTO `allrecord` VALUES (126, 'F0398D43', NULL, '00:03:51', '00:00:07', 22);
INSERT INTO `allrecord` VALUES (127, 'F0398D43', NULL, '00:03:55', '00:00:11', 22);
INSERT INTO `allrecord` VALUES (128, 'F0398D43', '00:03:57', NULL, NULL, 22);
INSERT INTO `allrecord` VALUES (129, 'F0398D43', NULL, '00:03:58', '00:00:01', 22);
INSERT INTO `allrecord` VALUES (130, 'F0398D43', NULL, '00:03:59', '00:00:02', 22);
INSERT INTO `allrecord` VALUES (131, 'F0398D43', NULL, '00:04:01', '00:00:04', 22);
INSERT INTO `allrecord` VALUES (132, 'F0398D43', NULL, '00:04:05', '00:00:08', 26);
INSERT INTO `allrecord` VALUES (133, '50A18B43', NULL, '00:04:26', '00:02:21', 31);
INSERT INTO `allrecord` VALUES (134, '50A18B43', NULL, '00:04:29', '00:02:24', 28);
INSERT INTO `allrecord` VALUES (135, '50A18B43', NULL, '00:04:33', '00:02:28', 38);
INSERT INTO `allrecord` VALUES (136, '50A18B43', '00:00:44', NULL, NULL, 23);
INSERT INTO `allrecord` VALUES (137, '50A18B43', NULL, '00:01:12', '00:00:28', 23);
INSERT INTO `allrecord` VALUES (138, '50A18B43', NULL, '00:01:32', '00:00:48', 25);
INSERT INTO `allrecord` VALUES (139, '50A18B43', NULL, '00:01:34', '00:00:50', 24);
INSERT INTO `allrecord` VALUES (140, '50A18B43', NULL, '00:01:34', '00:00:50', 23);
INSERT INTO `allrecord` VALUES (141, '50A18B43', NULL, '00:01:37', '00:00:53', 17);
INSERT INTO `allrecord` VALUES (142, '50A18B43', NULL, '00:01:39', '00:00:55', 18);
INSERT INTO `allrecord` VALUES (143, '50A18B43', NULL, '00:02:05', '00:01:21', 23);
INSERT INTO `allrecord` VALUES (144, '50A18B43', '00:02:17', NULL, NULL, 26);
INSERT INTO `allrecord` VALUES (145, '50A18B43', '00:02:18', NULL, NULL, 26);
INSERT INTO `allrecord` VALUES (146, '50A18B43', '00:02:18', NULL, NULL, 26);
INSERT INTO `allrecord` VALUES (147, '50A18B43', '00:02:19', NULL, NULL, 26);
INSERT INTO `allrecord` VALUES (148, '50A18B43', '00:02:19', NULL, NULL, 26);

-- ----------------------------
-- Table structure for enter
-- ----------------------------
DROP TABLE IF EXISTS `enter`;
CREATE TABLE `enter`  (
  `in_num` int(0) NOT NULL AUTO_INCREMENT,
  `in_card_id` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `in_time` time(0) NOT NULL,
  `howlong` time(0) NOT NULL,
  `in_temperature` int(0) NULL DEFAULT NULL,
  PRIMARY KEY (`in_num`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 74 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of enter
-- ----------------------------
INSERT INTO `enter` VALUES (84, 'F0398D43', '00:03:49', '00:00:05', 22);
INSERT INTO `enter` VALUES (85, 'F0398D43', '00:03:51', '00:00:07', 22);
INSERT INTO `enter` VALUES (86, 'F0398D43', '00:03:55', '00:00:11', 22);
INSERT INTO `enter` VALUES (87, 'F0398D43', '00:03:58', '00:00:01', 22);
INSERT INTO `enter` VALUES (88, 'F0398D43', '00:03:59', '00:00:02', 22);
INSERT INTO `enter` VALUES (89, 'F0398D43', '00:04:01', '00:00:04', 22);
INSERT INTO `enter` VALUES (90, 'F0398D43', '00:04:05', '00:00:08', 26);
INSERT INTO `enter` VALUES (91, '50A18B43', '00:04:26', '00:02:21', 31);
INSERT INTO `enter` VALUES (92, '50A18B43', '00:04:29', '00:02:24', 28);
INSERT INTO `enter` VALUES (93, '50A18B43', '00:04:33', '00:02:28', 38);
INSERT INTO `enter` VALUES (94, '50A18B43', '00:01:12', '00:00:28', 23);
INSERT INTO `enter` VALUES (95, '50A18B43', '00:01:32', '00:00:48', 25);
INSERT INTO `enter` VALUES (96, '50A18B43', '00:01:34', '00:00:50', 24);
INSERT INTO `enter` VALUES (97, '50A18B43', '00:01:34', '00:00:50', 23);
INSERT INTO `enter` VALUES (98, '50A18B43', '00:01:37', '00:00:53', 17);
INSERT INTO `enter` VALUES (99, '50A18B43', '00:01:39', '00:00:55', 18);
INSERT INTO `enter` VALUES (100, '50A18B43', '00:02:05', '00:01:21', 23);

-- ----------------------------
-- Table structure for goout
-- ----------------------------
DROP TABLE IF EXISTS `goout`;
CREATE TABLE `goout`  (
  `out_num` int(0) NOT NULL AUTO_INCREMENT,
  `out_card_id` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `out_time` time(0) NOT NULL,
  `out_temperature` int(0) NULL DEFAULT NULL,
  PRIMARY KEY (`out_num`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 34 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of goout
-- ----------------------------
INSERT INTO `goout` VALUES (61, 'F0398D43', '00:03:44', 22);
INSERT INTO `goout` VALUES (62, 'F0398D43', '00:03:57', 22);
INSERT INTO `goout` VALUES (63, '50A18B43', '00:00:44', 23);
INSERT INTO `goout` VALUES (64, '50A18B43', '00:02:17', 26);
INSERT INTO `goout` VALUES (65, '50A18B43', '00:02:18', 26);
INSERT INTO `goout` VALUES (66, '50A18B43', '00:02:18', 26);
INSERT INTO `goout` VALUES (67, '50A18B43', '00:02:19', 26);
INSERT INTO `goout` VALUES (68, '50A18B43', '00:02:19', 26);

-- ----------------------------
-- Table structure for student
-- ----------------------------
DROP TABLE IF EXISTS `student`;
CREATE TABLE `student`  (
  `card_id` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `sno` char(12) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`card_id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of student
-- ----------------------------
INSERT INTO `student` VALUES ('50A18B43', '3118001454');
INSERT INTO `student` VALUES ('87758369', '3218005537');

-- ----------------------------
-- Triggers structure for table enter
-- ----------------------------
DROP TRIGGER IF EXISTS `newenter`;
delimiter ;;
CREATE TRIGGER `newenter` AFTER INSERT ON `enter` FOR EACH ROW BEGIN
 INSERT INTO allrecord(all_card_id,all_in_time,all_howlong,all_temperature) 
	VALUES(new.in_card_id,new.in_time,new.howlong,new.in_temperature);
END
;;
delimiter ;

-- ----------------------------
-- Triggers structure for table goout
-- ----------------------------
DROP TRIGGER IF EXISTS `newgoout`;
delimiter ;;
CREATE TRIGGER `newgoout` AFTER INSERT ON `goout` FOR EACH ROW BEGIN
 INSERT INTO allrecord(all_card_id,all_out_time,all_temperature) 
	VALUES(new.out_card_id,new.out_time,new.out_temperature);
END
;;
delimiter ;

SET FOREIGN_KEY_CHECKS = 1;
