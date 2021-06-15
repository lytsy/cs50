-- phpMyAdmin SQL Dump
-- version 4.0.8
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1:3306
-- Generation Time: Mar 22, 2021 at 11:48 PM
-- Server version: 5.1.71-community-log
-- PHP Version: 5.5.4

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `pset8`
--

-- --------------------------------------------------------

--
-- Table structure for table `places`
--

CREATE TABLE IF NOT EXISTS `places` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `country_code` char(2) NOT NULL,
  `postal_code` varchar(20) NOT NULL,
  `place_name` varchar(180) NOT NULL,
  `admin_name1` varchar(100) NOT NULL,
  `admin_code1` varchar(20) NOT NULL,
  `admin_name2` varchar(100) NOT NULL,
  `admin_code2` varchar(20) NOT NULL,
  `admin_name3` varchar(100) NOT NULL,
  `admin_code3` varchar(20) NOT NULL,
  `latitude` decimal(7,4) NOT NULL,
  `longitude` decimal(7,4) NOT NULL,
  `accuracy` tinyint(4) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `country_code` (`country_code`),
  KEY `postal_code` (`postal_code`),
  KEY `place_name` (`place_name`),
  KEY `admin_name1` (`admin_name1`),
  KEY `admin_code1` (`admin_code1`),
  KEY `admin_name2` (`admin_name2`),
  KEY `admin_code2` (`admin_code2`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
